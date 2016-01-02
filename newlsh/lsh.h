#pragma once
#include <random>
#include <vector>
#include <map>
#include <algorithm>
#include <ctime>
#include <set>


using namespace std;

struct element
{
    int gid;
    double val;
};


struct Parameter_rbslsh
{
	/// Hash table size
   	unsigned M;
	/// Number of hash tables
    unsigned L;
    /// Dimension of the vector, it can be obtained from the instance of Matrix
    unsigned D;
    /// Binary code bytes
    unsigned N;
    /// The Difference between upper and lower bound of each dimension
    unsigned C;
};

struct Parameter_psdlsh
{
    /// Hash table size
    unsigned M;
    /// Number of hash tables
    unsigned L;
    /// Dimension of the vector, it can be obtained from the instance of Matrix
    unsigned D;
    /// Index mode, you can choose 1(CAUCHY) or 2(GAUSSIAN)
    unsigned T;
    /// Window size
    float W;
};

struct Parameter_rhplsh
{
    /// Hash table size
    unsigned M;
    /// Number of hash tables
    unsigned L;
    /// Dimension of the vector, it can be obtained from the instance of Matrix
    unsigned D;
    /// Binary code bytes
    unsigned N;
};

struct Parameter_thlsh
{
    /// Hash table size
    unsigned M;
    /// Number of hash tables
    unsigned L;
    /// Dimension of the vector, it can be obtained from the instance of Matrix
    unsigned D;
    /// Binary code bytes
    unsigned N;
    /// Upper bound of each dimension
    float Max;
    /// Lower bound of each dimension
    float Min;
};

class rbsLsh
{
private:
    Parameter_rbslsh param;
    std::vector<std::vector<unsigned> > rndBits;
    std::vector<std::vector<unsigned> > rndArray;
    std::vector<std::map<unsigned, std::vector<unsigned> > > tables;
public: 
    rbsLsh() {}
    rbsLsh(const Parameter_rbslsh &param_)
    {
        reset(param_);
    }
    ~rbsLsh() {}
    /**
     * Reset the parameter setting
     *
     * @param param_ A instance of rbsLsh::Parametor, which contains the necessary
     * parameters
     */
    void reset(const Parameter_rbslsh &param_)
    {
        param = param_;
        tables.resize(param.L);
        rndBits.resize(param.L);
        rndArray.resize(param.L);
        std::mt19937 rng(unsigned(std::time(0)));
        std::uniform_int_distribution<unsigned> usBits(0, param.D * param.C - 1);
        for (std::vector<std::vector<unsigned> >::iterator iter = rndBits.begin(); iter != rndBits.end(); ++iter)
        {
            while (iter->size() != param.N)
            {
                unsigned target = usBits(rng);
                if (std::find(iter->begin(), iter->end(), target) == iter->end())
                {
                    iter->push_back(target);
                }
            }
            std::sort(iter->begin(), iter->end());
        }
        std::uniform_int_distribution<unsigned> usArray(0, param.M - 1);
        for (std::vector<std::vector<unsigned> >::iterator iter = rndArray.begin(); iter != rndArray.end(); ++iter)
        {
            for (unsigned i = 0; i != param.N; ++i)
            {
                iter->push_back(usArray(rng));
            }
        }
    }
    /**
     * Insert a vector to the index.
     *
     * @param key   The sequence number of vector
     * @param domin The pointer to the vector
     */
    void insert(unsigned key, std::vector <unsigned> domin)
    {
        for (unsigned i = 0; i != param.L; ++i)
        {
            unsigned sum(0), seq(0);
            for (std::vector<unsigned>::iterator it = rndBits[i].begin(); it != rndBits[i].end(); ++it)
            {
                if ((*it % param.C) <= unsigned(domin[*it / param.C]))
                {
                    //std::cout << *it/param.C << std::endl;
                    //std::cout << domin[*it / param.C]<< std::endl;
                    //int a;
                    //std::cin >> a;
                    sum += rndArray[i][seq];
                }
                ++seq;
            }
            unsigned hashVal = sum % param.M;
            //std::cout <<"hash value: " << hashVal << std::endl;
            tables[i][hashVal].push_back(key);
        }
    }

    std::set<unsigned> query(std::vector <unsigned> domin)
    {
        //for each hash table
        std::set <unsigned> candidates;
        for(unsigned i = 0; i != param.L; ++i)      
        {
            unsigned sum(0), seq(0);
            for(std::vector<unsigned>::iterator it = rndBits[i].begin(); it != rndBits[i].end(); it++)
            {
                if ((*it % param.C) <= unsigned(domin[*it / param.C]))
                {
                    sum += rndArray[i][seq];
                }
                ++seq;
            }
            //std::cout <<sum << std::endl;
            unsigned hashVal = sum % param.M;
            //std::cout << hashVal << std::endl;
            if (tables[i].find(hashVal) != tables[i].end())
            {
                unsigned num(0);
                for (std::vector<unsigned>::iterator iter = tables[i][hashVal].begin(); iter != tables[i][hashVal].end(); ++iter)
                {
                    //std::cout << *iter << " ";
                    candidates.insert(*iter);
                    num++;
                }
                //std::cout << std::endl;
                //std::cout << "There are " << candidates.size() << std::endl;                
                //std::cout << "There are " << candidates.size() << " candidate for the trajectory" << std::endl;
            }
            else
                std::cout << "no matched" << std::endl;
        }
        return candidates;

    }
};
class psdLsh
{
#define CAUCHY   1
#define GAUSSIAN 2
private:
    Parameter_psdlsh param;
    std::vector<float> rndBs;
    std::vector<std::vector<float> > stableArray;
    std::vector<std::map<unsigned, std::vector<unsigned> > > tables;
public:
    psdLsh() {}
    psdLsh(const Parameter_psdlsh &param_)
    {
        reset(param_);
    }
    ~psdLsh() {}
    /**
     * Reset the parameter setting
     *
     * @param param_ A instance of psdLsh<DATATYPE>::Parametor, which contains
     * the necessary parameters
     */
    void reset(const Parameter_psdlsh &param_)
    {
        param = param_;
        tables.resize(param.L);
        stableArray.resize(param.L);
        std::mt19937 rng(unsigned(std::time(0)));
        //std::cout << rng << std::endl;
        std::uniform_real_distribution<float> ur(0, param.W);
        switch (param.T)
        {
        case CAUCHY:
        {
            std::cauchy_distribution<float> cd;
            for (std::vector<std::vector<float> >::iterator iter = stableArray.begin(); iter != stableArray.end(); ++iter)
            {
                for (unsigned i = 0; i != param.D; ++i)
                {
                    iter->push_back(cd(rng));
                }
                rndBs.push_back(ur(rng));
            }
            return;
        }
        case GAUSSIAN:
        {
            std::normal_distribution<float> nd;
            //std::cout << "size of stableArray is: " << stableArray.size() << std::endl;
            for (std::vector<std::vector<float> >::iterator iter = stableArray.begin(); iter != stableArray.end(); ++iter)
            {
                for (unsigned i = 0; i != param.D; ++i)
                {
                    iter->push_back(nd(rng));
                }
                rndBs.push_back(ur(rng));
            }
            return;
        }
        default:
        {
            return;
        }
        }
    }
    /**
     * Insert a vector to the index.
     *
     * @param key   The sequence number of vector
     * @param domin The pointer to the vector
     */
    void insert(unsigned key,  std::vector <double> domin)
    {
        for (unsigned i = 0; i != param.L; ++i)
        {
            float sum(0);
            for (unsigned j = 0; j != param.D; ++j)
            {
                sum += domin[j] * stableArray[i][j];
            }
            unsigned hashVal = unsigned(std::floor((sum + rndBs[i]) / param.W)) % param.M;
            tables[i][hashVal].push_back(key);
        }
    }
    /**
     * Query the approximate nearest neighborholds.
     *
     * @param domin   The pointer to the vector
     * @param scanner Top-K scanner, use for scan the approximate nearest neighborholds
     */
    //template <typename SCANNER>
    std::set <unsigned> query(std::vector <double> domin)
    {
        std::set <unsigned> candidates;
        for (unsigned i = 0; i != param.L; ++i)
        {
            float sum(0);
            for (unsigned j = 0; j != param.D; ++j)
            {
                sum += domin[j] * stableArray[i][j];
            }
            unsigned hashVal = unsigned(std::floor((sum + rndBs[i]) / param.W)) % param.M;
            if (tables[i].find(hashVal) != tables[i].end())
            {
                for (std::vector<unsigned>::iterator iter = tables[i][hashVal].begin(); iter != tables[i][hashVal].end(); ++iter)
                {
                    candidates.insert(*iter);
                }
            }
            else
                std::cout << "no matched" << std::endl;
        }
        return candidates;
    }
};

class rhpLsh
{
private:
    Parameter_rhplsh param;
    std::vector<std::vector<unsigned> > rndArray;
    std::vector<std::vector<std::vector<float> > > uosArray;
    std::vector<std::map<unsigned, std::vector<unsigned> > > tables;
public:
    rhpLsh() {}
    rhpLsh(const Parameter_rhplsh &param_)
    {
        reset(param_);
    }
    ~rhpLsh() {}
    /**
     * Reset the parameter setting
     *
     * @param param_ A instance of rhpLsh<DATATYPE>::Parametor, which contains
     * the necessary parameters
     */
    void reset(const Parameter_rhplsh &param_)
    {
        param = param_;
        tables.resize(param.L);
        uosArray.resize(param.L);
        rndArray.resize(param.L);
        std::mt19937 rng(unsigned(std::time(0)));
        std::normal_distribution<float> nd;
        std::uniform_int_distribution<unsigned> usArray(0, param.M - 1);
        for (std::vector<std::vector<std::vector<float> > >::iterator ithRb = uosArray.begin(); ithRb != uosArray.end(); ++ithRb)
        {
            ithRb->resize(param.N);
            for (std::vector<std::vector<float> >::iterator iter = ithRb->begin(); iter != ithRb->end(); ++iter)
            {
                for (unsigned k = 0; k != param.D; ++k)
                {
                    iter->push_back(nd(rng));
                }
            }
        }
        for (std::vector<std::vector<unsigned> >::iterator iter = rndArray.begin(); iter != rndArray.end(); ++iter)
        {
            for (unsigned i = 0; i != param.N; ++i)
            {
                iter->push_back(usArray(rng));
            }
        }
    }
    /**
     * Insert a vector to the index.
     *
     * @param key   The sequence number of vector
     * @param domin The pointer to the vector
     */
    void insert(unsigned key, vector<element>  domin)
    {
        for (unsigned i = 0; i != param.L; ++i)
        {
            unsigned sum(0);
            for (unsigned j = 0; j != param.N; ++j)
            {
                float flag(0);
              /*  for (unsigned k = 0; k != param.D; ++k)
                {
                    flag += uosArray[i][j][k] * domin[k];
                }*/
                 int size = domin.size();
                    for(unsigned k = 0; k < size; k++)
                    {
                        flag += uosArray[i][j][domin[k].gid] * domin[k].val;
                    }
                if (flag > 0)
                {
                    sum += rndArray[i][j];
                }
            }
            unsigned hashVal = sum % param.M;
            tables[i][hashVal].push_back(key);
        }
    }
    /**
     * Query the approximate nearest neighborholds.
     */
    //template <typename SCANNER>
    std::set <unsigned> query(std::vector <element>  domin)
    {
        std::set <unsigned> candidates;
        for (unsigned i = 0; i != param.L; ++i)
        {
            unsigned sum(0);
            for (unsigned j = 0; j != param.N; ++j)
            {
                float flag(0);
                /*for (unsigned k = 0; k != param.D; ++k)
                {
                    flag += uosArray[i][j][k] * domin[k];
                }*/
                 int size = domin.size();
                    for(unsigned k = 0; k < size; k++)
                    {
                        flag += uosArray[i][j][domin[k].gid] * domin[k].val;
                    }
                if (flag > 0)
                {
                    sum += rndArray[i][j];
                }
               /* else
                    std::cout << "flag < 0" << std::endl;*/
            }
            unsigned hashVal = sum % param.M;
            //std::cout << hashVal << std::endl;
            if (tables[i].find(hashVal) != tables[i].end())
            {
               // std::cout << tables[i][hashVal].size() << std::endl;
                for (std::vector<unsigned>::iterator iter = tables[i][hashVal].begin(); iter != tables[i][hashVal].end(); ++iter)
                {
                    candidates.insert(*iter);
                    //scanner(*iter);
                }
            }
        }
        return candidates;
    }
};

class thLsh
{
private:
    Parameter_thlsh param;
    std::vector<float> threadholds;
    std::vector<std::vector<unsigned> > rndBits;
    std::vector<std::vector<unsigned> > rndArray;
    std::vector<std::map<unsigned, std::vector<unsigned> > > tables;
public:
    thLsh() {}
    thLsh(const Parameter_thlsh &param_)
    {
        reset(param_);
    }
    ~thLsh() {}
    /**
     * Reset the parameter setting
     *
     * @param param_ A instance of thLsh<DATATYPE>::Parametor, which contains
     * the necessary parameters
     */
    void reset(const Parameter_thlsh &param_)
    {
        param = param_;
        tables.resize(param.L);
        rndBits.resize(param.L);
        rndArray.resize(param.L);
        std::mt19937 rng(unsigned(std::time(0)));
        std::uniform_int_distribution<unsigned> usBits(0, param.D - 1);
        std::uniform_int_distribution<unsigned> usArray(0, param.M - 1);
        std::uniform_real_distribution<float> urThreadholds(param.Min, param.Max);
        for (unsigned i = 0; i != param.L; ++i)
        {
            while (rndBits[i].size() != param.N)
            {
                unsigned target = usBits(rng);
                if (std::find(rndBits[i].begin(), rndBits[i].end(), target) == rndBits[i].end())
                {
                    rndBits[i].push_back(target);
                }
            }
            std::sort(rndBits[i].begin(), rndBits[i].end());
            threadholds.push_back(urThreadholds(rng));
        }
        for (std::vector<std::vector<unsigned> >::iterator iter = rndArray.begin(); iter != rndArray.end(); ++iter)
        {
            for (unsigned i = 0; i != param.N; ++i)
            {
                iter->push_back(usArray(rng));
            }
        }
    }
    /**
     * Insert a vector to the index.
     *
     * @param key   The sequence number of vector
     * @param domin The pointer to the vector
     */
    void insert(unsigned key, std::vector <unsigned> domin)
    {
        for (unsigned i = 0; i != param.L; ++i)
        {
            unsigned sum(0), seq(0);
            for (std::vector<unsigned>::iterator it = rndBits[i].begin(); it != rndBits[i].end(); ++it)
            {
                if (domin[*it] > threadholds[seq])
                {
                    sum += rndArray[i][seq];
                }
                ++seq;
            }
            unsigned hashVal = sum % param.M;
            tables[i][hashVal].push_back(key);
        }
    }
    /**
     * Query the approximate nearest neighborholds.
     *
     * @param domin   The pointer to the vector
     * @param scanner Top-K scanner, use for scan the approximate nearest neighborholds
     */
    //template <typename SCANNER>
    std::set <unsigned> query(std::vector <unsigned> domin)
    {
        std::set <unsigned> candidates;
        for (unsigned i = 0; i != param.L; ++i)
        {
            unsigned sum(0), seq(0);
            for (std::vector<unsigned>::iterator it = rndBits[i].begin(); it != rndBits[i].end(); ++it)
            {
                if (domin[*it] > threadholds[seq])
                {
                    sum += rndArray[i][seq];
                }
                ++seq;
            }
            unsigned hashVal = sum % param.M;
            if (tables[i].find(hashVal) != tables[i].end())
            {
                for (std::vector<unsigned>::iterator iter = tables[i][hashVal].begin(); iter != tables[i][hashVal].end(); ++iter)
                {
                    candidates.insert(*iter);
                }
            }
            else
                std::cout << "no matched" << std::endl;
        }
        return candidates;
    }
};