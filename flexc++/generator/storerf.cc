#include "generator.ih"

// called from dfarfs.cc

void Generator::storeRF(pair<size_t, size_t> &final,
                         vector<RuleFlag> &rfs)
{
    size_t rule = -1; //tailCount.rule();

    RuleFlag rf {rule, 0};

    rf.d_flag = 0;

    if (final.first == rule)
    {
        final.first = max<size_t>();
        rf.d_flag |= FINAL | BOL;
    }

    if (final.second == rule)
    {
        final.second = max<size_t>();
        rf.d_flag |= FINAL;
    }

    if (rf.d_flag != 0)
        rfs.push_back(rf);
}



