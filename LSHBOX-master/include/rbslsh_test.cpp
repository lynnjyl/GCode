//////////////////////////////////////////////////////////////////////////////
/// Copyright (C) 2014 Gefu Tang <tanggefu@gmail.com>. All Rights Reserved.
///
/// This file is part of LSHBOX.
///
/// LSHBOX is free software: you can redistribute it and/or modify it under
/// the terms of the GNU General Public License as published by the Free
/// Software Foundation, either version 3 of the License, or(at your option)
/// any later version.
///
/// LSHBOX is distributed in the hope that it will be useful, but WITHOUT
/// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
/// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
/// more details.
///
/// You should have received a copy of the GNU General Public License along
/// with LSHBOX. If not, see <http://www.gnu.org/licenses/>.
///
/// @version 0.1
/// @author Gefu Tang & Zhifeng Xiao
/// @date 2014.6.30
//////////////////////////////////////////////////////////////////////////////

/**
 * @file rbslsh-run.cpp
 *
 * @brief Example of using Random Bits Sampling LSH index for L2 distance.
 */
#include "lshbox.h"
int main(int argc, char const *argv[])
{
    std::cout << "Example of using Random Bits Sampling LSH" << std::endl << std::endl;
    std::cout << "LOADING DATA ..." << std::endl;
    lshbox::timer timer;
    lshbox::Matrix<unsigned> data("unsigned.data");
    std::cout << "LOAD TIME: " << timer.elapsed() << "s." << std::endl;
    std::cout << "CONSTRUCTING INDEX ..." << std::endl;
    timer.restart();
    std::string file = "rbs.lsh";
    bool use_index = false;
    lshbox::rbsLsh mylsh;
    if (use_index)
    {
        mylsh.load(file);
    }
    else
    {
        lshbox::rbsLsh::Parameter param;
        param.M = 521;              // Hash table size
        param.L = 5;                // Number of hash tables
        param.D = data.getDim();    // Dimension of the vector, it can be obtained from the instance of Matrix
        param.C = 5; //���ֵ       // Binary code bytes
        param.N = 20;               // The Difference between upper and lower bound of each dimension
        mylsh.reset(param);
        lshbox::progress_display pd(data.getSize());
        for (unsigned i = 0; i != data.getSize(); ++i)
        {
            mylsh.insert(i, data[i]);
            ++pd;
        }
    }
    mylsh.save(file);
    std::cout << "CONSTRUCTING TIME: " << timer.elapsed() << "s." << std::endl;
    std::cout << "LOADING BENCHMARK ..." << std::endl;
    timer.restart();
    lshbox::Matrix<unsigned>::Accessor accessor(data);
    lshbox::Metric<unsigned> metric(data.getDim(), L1_DIST);
    lshbox::Benchmark bench;
    std::string benchmark("unsigned.ben");
    bench.load(benchmark);
    unsigned K = bench.getK();
    lshbox::Scanner<lshbox::Matrix<unsigned>::Accessor> scanner(
        accessor,
        metric,
        K,
        std::numeric_limits<float>::max()
    );
    std::cout << "LOADING TIME: " << timer.elapsed() << "s." << std::endl;
    std::cout << "RUNING QUERY ..." << std::endl;
    timer.restart();
    lshbox::Stat cost, recall;
    lshbox::progress_display pd(bench.getQ());
    for (unsigned i = 0; i != bench.getQ(); ++i)
    {
        scanner.reset(data[bench.getQuery(i)]);
        mylsh.query(data[bench.getQuery(i)], scanner);
        recall << bench.getAnswer(i).recall(scanner.topk());
        cost << float(scanner.cnt()) / float(data.getSize());
        ++pd;
    }
    std::cout << "MEAN QUERY TIME: " << timer.elapsed() / bench.getQ() << "s." << std::endl;
    std::cout << "RECALL: " << recall.getAvg() << " +/- " << recall.getStd() << std::endl;
    std::cout << "COST  : " << cost.getAvg() << " +/- " << cost.getStd() << std::endl;
    /*
    for (int i=0; i != 100; ++i)
    {
        std::cout << "---------- QUERY " << i+1  << " ----------" << std::endl;
        scanner.reset(data[i]);
        mylsh.query(data[i], scanner);
        std::vector<std::pair<unsigned, float> > result = scanner.topk().getTopk();
        for (std::vector<std::pair<unsigned, float> >::iterator it = result.begin(); it != result.end(); ++it)
        {
            std::cout << it->first << ", " << it->second << std::endl;
        }
        std::cout << "VISIT: " << scanner.cnt() << std::endl;
        getchar();
    }
    */
}