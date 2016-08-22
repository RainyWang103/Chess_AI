//
//  2_KingRook_Status.h
//  Chess
//
//  Created by WangYuli on 29/11/2015.
//  Copyright © 2015 WangYuli. All rights reserved.
//

#ifndef KingRook_Status_h
#define KingRook_Status_h
class KingRook_Marker
{
private:
    bool marker[2][3];
    int Mapped_side(const int& x);
    int Mapped_location(const int& y);
public:
    KingRook_Marker();
    void Set_KR_Moved(const int& x, const int& y);
    bool Get_KR_Moved(const int& x, const int& y);
};

KingRook_Marker::KingRook_Marker(){
    for(int i=0; i<2;i++)
        for(int j=0; j<3; j++)
            marker[i][j]=false; // set as not moved
}

void KingRook_Marker::Set_KR_Moved(const int &x, const int &y){
    int index_x = Mapped_side(x);
    int index_y = Mapped_location(y);
    marker[index_x][index_y]=true;
}

bool KingRook_Marker::Get_KR_Moved(const int &x, const int &y){
    int index_x = Mapped_side(x);
    int index_y = Mapped_location(y);
    return marker[index_x][index_y];
}

int KingRook_Marker::Mapped_side(const int &x){
    if(x==0) return 0;
    return 1;
}

int KingRook_Marker::Mapped_location(const int &y){
    return (y-1)/3;
}


#endif /* KingRook_Status_h */
