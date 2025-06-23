#if !defined(RANDOM_H)
#define RANDOM_H

#include <Arduino.h>

int predict(float *x)
{
    uint8_t votes[2] = {0};
    // tree #1
    if (x[3] <= 2.134999990463257)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #2
    if (x[0] <= 350.8500061035156)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #3
    if (x[0] <= 351.0)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #4
    if (x[3] <= 2.319999933242798)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #5
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #6
    if (x[0] <= 350.9499969482422)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #7
    if (x[3] <= 1.824999988079071)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #8
    if (x[2] <= 545.7050018310547)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #9
    if (x[2] <= 499.4200134277344)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #10
    if (x[1] <= 52.94999885559082)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #11
    if (x[3] <= 1.865000069141388)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #12
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #13
    if (x[1] <= 48.25500011444092)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #14
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #15
    if (x[1] <= 48.760000228881836)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #16
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #17
    if (x[3] <= 1.824999988079071)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #18
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #19
    if (x[2] <= 480.18499755859375)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #20
    if (x[3] <= 2.134999990463257)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #21
    if (x[1] <= 52.94999885559082)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #22
    if (x[3] <= 2.134999990463257)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #23
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #24
    if (x[2] <= 480.18499755859375)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #25
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #26
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #27
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #28
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #29
    if (x[2] <= 484.6400146484375)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #30
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #31
    if (x[2] <= 480.18499755859375)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #32
    if (x[3] <= 2.134999990463257)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #33
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #34
    if (x[1] <= 46.94000053405762)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #35
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #36
    if (x[1] <= 48.760000228881836)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #37
    if (x[1] <= 49.21999931335449)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #38
    if (x[1] <= 52.94999885559082)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #39
    if (x[3] <= 1.824999988079071)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #40
    if (x[2] <= 499.4200134277344)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #41
    if (x[1] <= 48.760000228881836)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #42
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #43
    if (x[3] <= 1.7649999856948853)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #44
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #45
    if (x[1] <= 48.760000228881836)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #46
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #47
    if (x[1] <= 52.94999885559082)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #48
    if (x[2] <= 480.18499755859375)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #49
    if (x[2] <= 471.97499084472656)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #50
    if (x[3] <= 2.134999990463257)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #51
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #52
    if (x[0] <= 350.8500061035156)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #53
    if (x[3] <= 1.9000000357627869)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #54
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #55
    if (x[3] <= 2.134999990463257)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #56
    if (x[3] <= 2.1799999475479126)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #57
    if (x[3] <= 1.824999988079071)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #58
    if (x[3] <= 1.824999988079071)
    {
        votes[0] += 1;
    }

    else
    {
        if (x[0] <= 353.34999084472656)
        {
            votes[1] += 1;
        }

        else
        {
            votes[0] += 1;
        }
    }

    // tree #59
    if (x[2] <= 476.4300079345703)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #60
    if (x[3] <= 1.824999988079071)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #61
    if (x[0] <= 351.0)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #62
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #63
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #64
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #65
    if (x[2] <= 480.18499755859375)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #66
    if (x[2] <= 482.28001403808594)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #67
    if (x[2] <= 499.4200134277344)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #68
    if (x[3] <= 2.134999990463257)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #69
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #70
    if (x[0] <= 350.9499969482422)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #71
    if (x[3] <= 1.7649999856948853)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #72
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #73
    if (x[1] <= 48.760000228881836)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #74
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #75
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #76
    if (x[0] <= 350.8500061035156)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #77
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #78
    if (x[1] <= 52.94999885559082)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #79
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #80
    if (x[3] <= 2.134999990463257)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #81
    if (x[2] <= 517.8800048828125)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #82
    if (x[3] <= 1.824999988079071)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #83
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #84
    if (x[3] <= 2.1799999475479126)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #85
    if (x[1] <= 48.760000228881836)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #86
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #87
    if (x[1] <= 52.94999885559082)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #88
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #89
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #90
    if (x[2] <= 499.4200134277344)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #91
    if (x[3] <= 2.134999990463257)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #92
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #93
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #94
    if (x[1] <= 48.714999198913574)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #95
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #96
    if (x[1] <= 48.760000228881836)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #97
    if (x[2] <= 480.18499755859375)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #98
    if (x[0] <= 349.65000915527344)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #99
    if (x[1] <= 52.94999885559082)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #100
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #101
    if (x[3] <= 2.134999990463257)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #102
    if (x[0] <= 350.8500061035156)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[3] <= 2.7149999141693115)
        {
            votes[0] += 1;
        }

        else
        {
            votes[1] += 1;
        }
    }

    // tree #103
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #104
    if (x[1] <= 48.714999198913574)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #105
    if (x[0] <= 350.9499969482422)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #106
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #107
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #108
    if (x[3] <= 2.134999990463257)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #109
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #110
    if (x[3] <= 1.7900000214576721)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #111
    if (x[0] <= 350.90000915527344)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #112
    if (x[2] <= 484.6400146484375)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #113
    if (x[1] <= 48.25500011444092)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #114
    if (x[3] <= 1.824999988079071)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #115
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #116
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #117
    if (x[1] <= 48.760000228881836)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #118
    if (x[1] <= 55.48000144958496)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #119
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #120
    if (x[1] <= 54.09499931335449)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #121
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #122
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #123
    if (x[1] <= 48.760000228881836)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #124
    if (x[0] <= 350.3500061035156)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #125
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #126
    if (x[3] <= 1.824999988079071)
    {
        votes[0] += 1;
    }

    else
    {
        if (x[1] <= 58.42500114440918)
        {
            votes[1] += 1;
        }

        else
        {
            votes[0] += 1;
        }
    }

    // tree #127
    if (x[1] <= 54.09499931335449)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #128
    if (x[1] <= 50.364999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #129
    if (x[2] <= 477.8249969482422)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #130
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #131
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #132
    if (x[1] <= 48.25500011444092)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #133
    if (x[3] <= 2.134999990463257)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #134
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #135
    if (x[3] <= 1.824999988079071)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #136
    if (x[1] <= 54.09499931335449)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #137
    if (x[2] <= 517.8800048828125)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #138
    if (x[1] <= 52.94999885559082)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #139
    if (x[0] <= 350.9499969482422)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #140
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #141
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #142
    if (x[3] <= 2.134999990463257)
    {
        if (x[0] <= 346.1499938964844)
        {
            votes[1] += 1;
        }

        else
        {
            votes[0] += 1;
        }
    }

    else
    {
        votes[1] += 1;
    }

    // tree #143
    if (x[3] <= 1.9000000357627869)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #144
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #145
    if (x[1] <= 54.90500068664551)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #146
    if (x[1] <= 52.94999885559082)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #147
    if (x[2] <= 499.4200134277344)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #148
    if (x[1] <= 52.489999771118164)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #149
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #150
    if (x[1] <= 54.62499809265137)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #151
    if (x[0] <= 350.9499969482422)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #152
    if (x[0] <= 350.8500061035156)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #153
    if (x[1] <= 54.09499931335449)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #154
    if (x[0] <= 350.9499969482422)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #155
    if (x[3] <= 1.7900000214576721)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #156
    if (x[2] <= 480.18499755859375)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #157
    if (x[3] <= 2.134999990463257)
    {
        votes[0] += 1;
    }

    else
    {
        votes[1] += 1;
    }

    // tree #158
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #159
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #160
    if (x[2] <= 494.9649963378906)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #161
    if (x[2] <= 482.28001403808594)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #162
    if (x[2] <= 480.18499755859375)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #163
    if (x[1] <= 48.760000228881836)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // return argmax of votes
    uint8_t classIdx = 0;
    float maxVotes = votes[0];

    for (uint8_t i = 1; i < 2; i++)
    {
        if (votes[i] > maxVotes)
        {
            classIdx = i;
            maxVotes = votes[i];
        }
    }

    return classIdx;
}

#endif