/* The MIT Licensem

   Copyright (c) 2013 Adrian Tan <atks@umich.edu>

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/

#include "version.h"
#include "view.h"
#include "math.h"

void print_time(double t)
{
    if (t<60)
    {
        fprintf(stderr, "Time elapsed: %.2fs\n\n", t);
    }
    else if (t<60*60) //less than an hour
    {
        fprintf(stderr, "Time elapsed: %dm %ds\n\n", ((int32_t)(t/60)), ((int32_t)fmod(t, 60)));
    }
    else if (t<60*60*24) //less than a day
    {
        double m = fmod(t, 60*60); //remaining minutes
        fprintf(stderr, "Time elapsed: %dh %dm %ds\n\n", ((int32_t)(t/(60*60))), ((int32_t)(m/60)), ((int32_t)fmod(m, 60)));
    }
    else if (t<60*60*24*365) //less than a year
    {
        double h = fmod(t, 60*60*24); //remaining hours
        double m = fmod(h, 60*60); //remaining minutes
        fprintf(stderr, "Time elapsed: %dd %dh %dm %ds\n\n", ((int32_t)(t/(60*60*24))), ((int32_t)(h/(60*60))), ((int32_t)(m/60)), ((int32_t)fmod(m, 60)));
    }
};

void help()
{
    std::clog << "Help page on http://shangri-la/wiki/Ft\n";
    std::clog << "\n";
    std::clog << "Useful tools:\n";
    std::clog << "view                     view vcf/vcf.gz/bcf files\n";
    std::clog << "stat                     index vcf.gz/bcf files\n";
    std::clog << "\n";
}

int main(int argc, char ** argv)
{
    clock_t t0;
    t0 = clock();
    bool print = true;

    if (argc==1)
    {
        help();
        exit(0);
    }

    std::string cmd(argv[1]);

    //primitive programs that do not require help pages and summary statistics by default
    if (argc==2 && (cmd=="--version" || cmd=="-v"))
    {
        std::clog << "vt v" << VERSION << "\n";
        std::clog << "The MIT license\n";
        std::clog << "Copyright (c) 2021 Adrian Tan <adrian_tan@nparks.gov.sg>\n";
        exit(0);
    }
//    else if (argc>1 && cmd=="view")
//    {
//        print = view(argc-1, ++argv);
//    }  
    else
    {
        std::clog << "Command not found: " << argv[1] << "\n\n";
        help();
        exit(1);
    }

    if (print)
    {
        clock_t t1;
        t1 = clock();
        print_time((float)(t1-t0)/CLOCKS_PER_SEC);
    }

    return 0;
}
