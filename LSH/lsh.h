#pragma once
#include <random>
#include <vector>
#include <map>
#include <algorithm>
#include <ctime>


struct Parameter
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

template <typename ACCESSOR>
class Scanner
{
public:
    typedef typename ACCESSOR::Value Value;
    typedef typename ACCESSOR::DATATYPE DATATYPE;
    /**
     * Constructor for this class.
     *
     * @param accessor The scanner use accessor to retrieva values from keys.
     * @param metric The distance metric.
     * @param K Value used to reset internal Topk class.
     * @param R Value used to reset internal Topk class.
     */
    Scanner(
        const ACCESSOR &accessor,
        const Metric<DATATYPE> &metric,
        unsigned K,
        float R = std::numeric_limits<float>::max()
    ): accessor_(accessor), metric_(metric), K_(K), R_(R), cnt_(0) {}
    /**
      * Reset the query, this function should be invoked before each query.
      */
    void reset(Value query)
    {
        query_ = query;
        accessor_.reset();
        topk_.reset(K_, R_);
        cnt_ = 0;
    }
    /**
     * Number of points scanned for the current query.
     */
    unsigned cnt() const
    {
        return cnt_;
    }
    /**
     * TopK results.
     */
    const Topk &topk() const
    {
        return topk_;
    }
    /**
     * TopK results.
     */
    Topk &topk()
    {
        return topk_;
    }
    /**
     * Update the current query by scanning key, this is normally invoked by the LSH
     * index structure.
     */
    void operator () (unsigned key)
    {
        if (accessor_.mark(key))
        {
            ++cnt_;
            topk_.push(key, metric_.dist(query_, accessor_(key)));
        }
    }
private:
    ACCESSOR accessor_;
    Metric<DATATYPE> metric_;
    Topk topk_;
    Value query_;
    unsigned K_;
    float R_;
    unsigned cnt_;
};


class rbsLsh
{
private:
    Parameter param;
    std::vector<std::vector<unsigned> > rndBits;
    std::vector<std::vector<unsigned> > rndArray;
    std::vector<std::map<unsigned, std::vector<unsigned> > > tables;
public: 
	rbsLsh() {}
    rbsLsh(const Parameter &param_)
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
    void reset(const Parameter &param_)
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
    void insert(unsigned key, unsigned *domin)
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
            std::cout <<"hash value: " << hashVal << std::endl;
            tables[i][hashVal].push_back(key);
        }
    }
    /**
     * Query the approximate nearest neighborholds.
     *
     * @param domin   The pointer to the vector
     * @param scanner Top-K scanner, use for scan the approximate nearest neighborholds
     */
    template <typename SCANNER>
    void query(unsigned *domin, SCANNER &scanner)
    {
        for (unsigned i = 0; i != param.L; ++i)
        {
            unsigned sum(0), seq(0);
            for (std::vector<unsigned>::iterator it = rndBits[i].begin(); it != rndBits[i].end(); ++it)
            {
                if ((*it % param.C) <= unsigned(domin[*it / param.C]))
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
                    scanner(*iter);
                }
            }
        }
    }

};