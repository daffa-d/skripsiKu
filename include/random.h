#if !defined(RANDOM_H)
#define RANDOM_H

int predict(float *x)
{
    uint8_t votes[2] = {0};
    // tree #1
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #2
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #3
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #4
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #5
    if (x[1] <= 1.425000011920929)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #6
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #7
    if (x[2] <= 83.26000213623047)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #8
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #9
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #10
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #11
    if (x[2] <= 76.0999984741211)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #12
    if (x[2] <= 84.44499969482422)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #13
    if (x[0] <= 8.120000123977661)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #14
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #15
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #16
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[2] <= 70.43500137329102)
        {
            votes[1] += 1;
        }

        else
        {
            votes[0] += 1;
        }
    }

    // tree #17
    if (x[2] <= 74.42499923706055)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #18
    if (x[2] <= 75.13000106811523)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #19
    if (x[2] <= 83.26000213623047)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #20
    if (x[0] <= 8.849999904632568)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[1] <= 1.4199999570846558)
        {
            votes[1] += 1;
        }

        else
        {
            votes[0] += 1;
        }
    }

    // tree #21
    if (x[2] <= 83.26000213623047)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #22
    if (x[1] <= 1.4199999570846558)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #23
    if (x[2] <= 83.26000213623047)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #24
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #25
    if (x[1] <= 1.4199999570846558)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #26
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #27
    if (x[2] <= 84.44499969482422)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #28
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #29
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #30
    if (x[2] <= 83.26000213623047)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #31
    if (x[1] <= 1.4300000071525574)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #32
    if (x[2] <= 83.26000213623047)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #33
    if (x[2] <= 83.26000213623047)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #34
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[1] <= 1.4199999570846558)
        {
            votes[1] += 1;
        }

        else
        {
            votes[0] += 1;
        }
    }

    // tree #35
    if (x[2] <= 85.08499908447266)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #36
    if (x[0] <= 9.0)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[0] <= 20.259999752044678)
        {
            votes[0] += 1;
        }

        else
        {
            votes[1] += 1;
        }
    }

    // tree #37
    if (x[2] <= 83.26000213623047)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #38
    if (x[2] <= 90.10499954223633)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #39
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #40
    if (x[0] <= 8.849999904632568)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[2] <= 71.61999893188477)
        {
            votes[1] += 1;
        }

        else
        {
            votes[0] += 1;
        }
    }

    // tree #41
    if (x[2] <= 74.2750015258789)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #42
    if (x[1] <= 1.4199999570846558)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #43
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #44
    if (x[2] <= 83.26000213623047)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #45
    if (x[0] <= 7.865000009536743)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #46
    if (x[1] <= 1.425000011920929)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #47
    if (x[2] <= 83.26000213623047)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #48
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[0] <= 20.259999752044678)
        {
            votes[0] += 1;
        }

        else
        {
            if (x[0] <= 33.69000053405762)
            {
                votes[1] += 1;
            }

            else
            {
                votes[0] += 1;
            }
        }
    }

    // tree #49
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #50
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #51
    if (x[0] <= 8.009999990463257)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #52
    if (x[2] <= 83.26000213623047)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #53
    if (x[1] <= 1.4199999570846558)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #54
    if (x[2] <= 83.26000213623047)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #55
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #56
    if (x[1] <= 1.4199999570846558)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #57
    if (x[0] <= 8.849999904632568)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #58
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[1] <= 1.4199999570846558)
        {
            votes[1] += 1;
        }

        else
        {
            votes[0] += 1;
        }
    }

    // tree #59
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #60
    if (x[1] <= 1.4149999618530273)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #61
    if (x[2] <= 90.10499954223633)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #62
    if (x[0] <= 8.009999990463257)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #63
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #64
    if (x[2] <= 84.44499969482422)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #65
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #66
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[0] <= 21.59999990463257)
        {
            votes[0] += 1;
        }

        else
        {
            votes[1] += 1;
        }
    }

    // tree #67
    if (x[1] <= 1.4199999570846558)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #68
    if (x[2] <= 83.26000213623047)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #69
    if (x[2] <= 74.2750015258789)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #70
    if (x[0] <= 8.009999990463257)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #71
    if (x[2] <= 84.44499969482422)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #72
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #73
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #74
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[0] <= 21.59999990463257)
        {
            votes[0] += 1;
        }

        else
        {
            if (x[0] <= 33.69000053405762)
            {
                votes[1] += 1;
            }

            else
            {
                votes[0] += 1;
            }
        }
    }

    // tree #75
    if (x[2] <= 85.08499908447266)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #76
    if (x[2] <= 85.08499908447266)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #77
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #78
    if (x[1] <= 1.4300000071525574)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #79
    if (x[0] <= 8.100000143051147)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[0] <= 21.59999990463257)
        {
            votes[0] += 1;
        }

        else
        {
            if (x[0] <= 33.69000053405762)
            {
                votes[1] += 1;
            }

            else
            {
                votes[0] += 1;
            }
        }
    }

    // tree #80
    if (x[1] <= 1.4199999570846558)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #81
    if (x[0] <= 7.865000009536743)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #82
    if (x[0] <= 7.865000009536743)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #83
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #84
    if (x[0] <= 8.009999990463257)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[0] <= 21.59999990463257)
        {
            votes[0] += 1;
        }

        else
        {
            if (x[0] <= 33.69000053405762)
            {
                votes[1] += 1;
            }

            else
            {
                votes[0] += 1;
            }
        }
    }

    // tree #85
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[2] <= 71.61999893188477)
        {
            votes[1] += 1;
        }

        else
        {
            votes[0] += 1;
        }
    }

    // tree #86
    if (x[2] <= 74.2750015258789)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #87
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #88
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #89
    if (x[1] <= 1.4199999570846558)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #90
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #91
    if (x[0] <= 8.849999904632568)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[1] <= 1.4199999570846558)
        {
            votes[1] += 1;
        }

        else
        {
            votes[0] += 1;
        }
    }

    // tree #92
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #93
    if (x[2] <= 76.95499801635742)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #94
    if (x[1] <= 1.4199999570846558)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #95
    if (x[0] <= 8.849999904632568)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #96
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #97
    if (x[0] <= 9.079999923706055)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[1] <= 1.4199999570846558)
        {
            votes[1] += 1;
        }

        else
        {
            votes[0] += 1;
        }
    }

    // tree #98
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #99
    if (x[2] <= 85.08499908447266)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #100
    if (x[1] <= 1.4199999570846558)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #101
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #102
    if (x[2] <= 85.08499908447266)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #103
    if (x[2] <= 83.26000213623047)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #104
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[2] <= 70.43500137329102)
        {
            votes[1] += 1;
        }

        else
        {
            votes[0] += 1;
        }
    }

    // tree #105
    if (x[2] <= 76.31499862670898)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #106
    if (x[2] <= 83.26000213623047)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #107
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #108
    if (x[0] <= 9.0)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #109
    if (x[2] <= 85.08499908447266)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #110
    if (x[1] <= 1.4199999570846558)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #111
    if (x[0] <= 7.700000047683716)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #112
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #113
    if (x[0] <= 8.009999990463257)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #114
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[2] <= 71.61999893188477)
        {
            votes[1] += 1;
        }

        else
        {
            votes[0] += 1;
        }
    }

    // tree #115
    if (x[1] <= 1.4300000071525574)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #116
    if (x[0] <= 9.0)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #117
    if (x[2] <= 74.2750015258789)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #118
    if (x[1] <= 1.4199999570846558)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #119
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #120
    if (x[2] <= 75.13000106811523)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #121
    if (x[1] <= 1.4199999570846558)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #122
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #123
    if (x[0] <= 8.100000143051147)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[0] <= 21.59999990463257)
        {
            votes[0] += 1;
        }

        else
        {
            if (x[0] <= 33.69000053405762)
            {
                votes[1] += 1;
            }

            else
            {
                votes[0] += 1;
            }
        }
    }

    // tree #124
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[1] <= 1.4199999570846558)
        {
            votes[1] += 1;
        }

        else
        {
            votes[0] += 1;
        }
    }

    // tree #125
    if (x[0] <= 8.100000143051147)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #126
    if (x[2] <= 85.08499908447266)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #127
    if (x[2] <= 84.44499969482422)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #128
    if (x[2] <= 75.13000106811523)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #129
    if (x[1] <= 1.4300000071525574)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #130
    if (x[0] <= 8.009999990463257)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[1] <= 1.4199999570846558)
        {
            votes[1] += 1;
        }

        else
        {
            votes[0] += 1;
        }
    }

    // tree #131
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[0] <= 21.59999990463257)
        {
            votes[0] += 1;
        }

        else
        {
            if (x[2] <= 77.27999877929688)
            {
                votes[1] += 1;
            }

            else
            {
                votes[0] += 1;
            }
        }
    }

    // tree #132
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[1] <= 1.4199999570846558)
        {
            votes[1] += 1;
        }

        else
        {
            votes[0] += 1;
        }
    }

    // tree #133
    if (x[2] <= 83.26000213623047)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #134
    if (x[2] <= 83.26000213623047)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #135
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[0] <= 21.59999990463257)
        {
            votes[0] += 1;
        }

        else
        {
            if (x[0] <= 33.69000053405762)
            {
                votes[1] += 1;
            }

            else
            {
                votes[0] += 1;
            }
        }
    }

    // tree #136
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #137
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #138
    if (x[2] <= 84.44499969482422)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #139
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #140
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[1] <= 1.4199999570846558)
        {
            votes[1] += 1;
        }

        else
        {
            votes[0] += 1;
        }
    }

    // tree #141
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #142
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[0] <= 21.59999990463257)
        {
            votes[0] += 1;
        }

        else
        {
            votes[1] += 1;
        }
    }

    // tree #143
    if (x[0] <= 8.759999752044678)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[2] <= 71.61999893188477)
        {
            votes[1] += 1;
        }

        else
        {
            votes[0] += 1;
        }
    }

    // tree #144
    if (x[2] <= 76.31499862670898)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #145
    if (x[2] <= 83.26000213623047)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #146
    if (x[2] <= 84.44499969482422)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #147
    if (x[0] <= 8.250000238418579)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[2] <= 71.61999893188477)
        {
            votes[1] += 1;
        }

        else
        {
            votes[0] += 1;
        }
    }

    // tree #148
    if (x[1] <= 1.4249999523162842)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #149
    if (x[2] <= 74.2750015258789)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #150
    if (x[2] <= 75.13000106811523)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #151
    if (x[0] <= 8.849999904632568)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #152
    if (x[0] <= 8.250000238418579)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[2] <= 71.61999893188477)
        {
            votes[1] += 1;
        }

        else
        {
            votes[0] += 1;
        }
    }

    // tree #153
    if (x[2] <= 75.45999908447266)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #154
    if (x[2] <= 84.44499969482422)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #155
    if (x[1] <= 1.425000011920929)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #156
    if (x[0] <= 7.609999895095825)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[1] <= 1.4199999570846558)
        {
            votes[1] += 1;
        }

        else
        {
            votes[0] += 1;
        }
    }

    // tree #157
    if (x[1] <= 1.4199999570846558)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #158
    if (x[0] <= 8.009999990463257)
    {
        votes[1] += 1;
    }

    else
    {
        if (x[2] <= 71.61999893188477)
        {
            votes[1] += 1;
        }

        else
        {
            votes[0] += 1;
        }
    }

    // tree #159
    if (x[2] <= 84.44499969482422)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #160
    if (x[2] <= 83.26000213623047)
    {
        votes[1] += 1;
    }

    else
    {
        votes[0] += 1;
    }

    // tree #161
    if (x[1] <= 1.4199999570846558)
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