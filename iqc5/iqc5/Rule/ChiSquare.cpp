//#include "ChiSquare.h"


//ChiSquare::ChiSquare()
//{

//}

//double GetChiSquare(const double alpha, const double dof)
//{

//    double limit = 100 -alpha;
//    int minIndex = 0;
//    double cur_d_value, min_d_value;
//    cur_d_value = min_d_value = abs(DofCode[0] - dof);
//    for(int i = 1; i < sizeof(DofCode)/sizeof(int); i++)
//    {
//        cur_d_value = abs(DofCode[i] - dof);
//        if(cur_d_value < min_d_value)
//        {
//            minIndex = i;
//            min_d_value = cur_d_value;
//        }
//    }
//    if(limit == 95)
//        return _95_[minIndex];
//    else if(limit == 99)
//        return _99_[minIndex];
//    else
//        return -1;
//}
