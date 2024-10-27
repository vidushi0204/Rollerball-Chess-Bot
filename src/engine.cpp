#include <algorithm>
#include <random>
#include <iostream>
#include <thread>
#include<queue>
#include <climits>
#include <ctime>
#include "board.hpp"
#include "engine.hpp"
#include "butils.hpp"
using namespace std;

int timeLimit,elapsedTime; 
chrono::_V2::steady_clock::time_point  startTime,currentTime;

class Node{
    public:
        U16 key = UINT16_MAX;
        int depth=0;
        U16 state=0;
        long long alpha = LONG_LONG_MIN;
        long long beta = LONG_LONG_MAX;
        long long int value=0;
    };
class Tree{
    public:
        Node* root;
        Tree(){
            root = new Node();
            root->depth=0;
            root->key=0;
        }};

int bp1[7][7]={{0,0,0,0,6,6,4},{0,0,0,0,10,13,9},{0,0,0,0,0,16,12},{0,0,0,0,0,19,15},{0,0,0,0,0,23,18},{0,0,0,32,29,26,22},{0,0,0,32,29,24,16}};
int wp1[7][7]={{16,25,29,32,0,0,0},{22,26,29,32,0,0,0},{18,23,0,0,0,0,0},{15,19,0,0,0,0,0},{12,16,0,0,0,0,0},{9,13,10,0,0,0,0},{4,6,6,0,0,0,0}};
int wrook1[7][7]={
{9,8,8,8,8,12,8}
,{13,4,1,1,1,4,8}
,{9,1,-1,-1,-1,0,8}
,{9,1,-1,-1,-1,0,8}
,{9,1,-1,-1,-1,0,8}
,{9,4,2,1,0,0,8}
,{9,12,7,7,5,6,6}};
int brook1[7][7]={
{6,6,5,7,7,12,9}
,{8,0,0,1,2,4,9}
,{8,0,-1,-1,-1,1,9}
,{8,0,-1,-1,-1,1,9}
,{8,0,-1,-1,-1,1,9}
,{8,4,1,1,1,4,13}
,{8,12,8,8,8,8,9}};

int bp2[8][8]={
{0,0,3,1,5,11,10,6},
{0,0,3,1,5,11,13,8},
{0,0,-1,-1,-1,-1,17,15},
{0,0,-1,-1,-1,-1,20,19},
{0,0,-1,-1,-1,-1,23,22},
{0,0,-1,-1,-1,-1,26,25},
{0,0,0,38,35,32,29,24},
{0,0,0,38,35,32,27,20}};
int wp2[8][8]={
{20,27,32,35,38,0,0,0},
{24,29,32,35,38,0,0,0},
{25,26,-1,-1,-1,-1,0,0},
{22,23,-1,-1,-1,-1,0,0},
{19,20,-1,-1,-1,-1,0,0},
{15,17,-1,-1,-1,-1,0,0},
{8,13,11,5,1,3,0,0},
{6,10,11,5,1,3,0,0}};

int wrook2[8][8]={
 {9,8,8,8,8,8,12,8}
,{13,4,1,1,1,1,4,8}
,{9,4,-1,-1,-1,-1,0,8}
,{9,4,-1,-1,-1,-1,0,8}
,{9,4,-1,-1,-1,-1,0,8}
,{9,4,-1,-1,-1,-1,0,8}
,{9,4,1,1,0,0,0,8}
,{9,12,7,7,7,5,6,6}};
int brook2[8][8]={
 {6,6,5,7,7,7,12,9}
,{9,0,0,0,1,1,4,8}
,{8,0,-1,-1,-1,-1,4,9}
,{8,0,-1,-1,-1,-1,4,9}
,{8,0,-1,-1,-1,-1,4,9}
,{8,0,-1,-1,-1,-1,4,9}
,{8,4,1,1,1,1,4,13}
,{8,12,8,8,8,8,8,9}};
int bp3[8][8]=
{{0,0,3,6,8,11,10,6},
{0,0,3,6,8,11,15,8},
{0,0,3,6,8,12,11,8},
{0,0,0,-1,-1,12,12,10},
{0,0,0,-1,-1,14,15,11},
{0,0,50,46,28,15,22,12},
{0,0,50,46,34,24,22,12},
{0,0,50,46,34,26,27,14}};
int wp3[8][8]=
{{14,27,26,34,46,50,0,0},
{12,22,24,34,46,50,0,0},
{12,22,15,28,46,50,0,0},
{11,15,14,-1,-1,0,0,0},
{10,12,12,-1,-1,0,0,0},
{8,16,11,8,6,3,0,0},
{8,15,11,8,6,3,0,0},
{6,10,11,8,6,3,0,0}};
int bp31[8][8]=
{{0,0,3,6,8,11,10,6},
{0,0,3,6,8,15,16,8},
{0,0,3,6,8,17,18,8},
{0,0,0,-1,-1,25,21,14},
{0,0,0,-1,-1,27,27,15},
{0,0,50,46,38,34,32,15},
{0,0,50,46,38,34,32,15},
{0,0,50,46,40,36,27,17}};
int wp31[8][8]=
{{17,27,36,40,46,50,0,0},
{15,32,34,38,46,50,0,0},
{15,32,34,38,46,50,0,0},
{15,27,27,-1,-1,0,0,0},
{14,21,25,-1,-1,0,0,0},
{8,18,17,8,6,3,0,0},
{8,15,11,8,6,3,0,0},
{6,10,11,8,6,3,0,0}};
int wrook3[8][8]=
{{8,8,8,8,8,8,12,8},
{12,4,1,1,1,1,4,8},
{12,4,1,1,1,1,4,8},
{8,1,1,-1,-1,4,2,8},
{8,1,1,-1,-1,4,2,8},
{8,6,1,1,1,1,4,9},
{8,6,1,1,1,1,4,9},
{8,12,6,6,6,6,6,6}};
int brook3[8][8]=
{{6,6,6,6,6,6,12,8},
{9,4,1,1,1,1,6,8},
{9,4,1,1,1,1,6,8},
{8,2,1,-1,-1,1,1,8},
{8,2,1,-1,-1,1,1,8},
{8,4,1,1,1,1,4,12},
{8,4,1,1,1,1,4,12},
{8,12,8,8,8,8,8,8}};

long long int pieces_73(Board &b){
    long long black_eval=0;
    long long white_eval=0;
    if(!(b.data.b_bishop== DEAD)) {
        {
            black_eval+=300;
            white_eval-=300;
        }
    }
    if(!(b.data.b_rook_1== DEAD)) {
        black_eval+=500;
        white_eval-=499;
    }
    if(!(b.data.b_rook_2== DEAD)) {
        black_eval+=500;
        white_eval-=499;
    }
    if(!(b.data.b_pawn_1== DEAD)) {
        if(b.data.b_pawn_1== BISHOP) {
            black_eval+=300;
            white_eval-=300;
        }
        else if (b.data.b_pawn_1== ROOK) {
            black_eval+=500;
            white_eval-=499;
        }
        else {
            black_eval+=90;
            white_eval-=89;
        }
    }
    if(!(b.data.b_pawn_2== DEAD)) {
        if(b.data.b_pawn_2== BISHOP) {
            black_eval+=300;
            white_eval-=300;
        }
        else if (b.data.b_pawn_2== ROOK) {
            black_eval+=500;
            white_eval-=499;
        }
        else  {
            black_eval+=90;
            white_eval-=89;
        }
    }

    if(!(b.data.w_bishop == DEAD)) {
        white_eval+=300;
        black_eval-=300;
    }
    if(!(b.data.w_rook_1== DEAD)) {
        white_eval+=500;
        black_eval-=499;
    } 
    if(!(b.data.w_rook_2== DEAD))  {
        white_eval+=500;
        black_eval-=499;
    }
    if(!(b.data.w_pawn_1 == DEAD)) {
        if(b.data.w_pawn_1 == BISHOP) {
            white_eval+=300;
            black_eval-=300;
        }
        else if (b.data.w_pawn_1 == ROOK) {
            white_eval+=500;
            black_eval-=499;
        }
        else {
            white_eval+=90;
            black_eval-=80;
        }
    }
    if(!(b.data.w_pawn_2== DEAD)) {
        if(b.data.w_pawn_2== BISHOP) {
            white_eval+=300;
            black_eval-=300;
        }
        else if (b.data.w_pawn_2== ROOK) {
            white_eval+=500;
            black_eval-=499;
        }
        else {
            white_eval+=90;
            black_eval-=80;
        }
    }
    
    if (b.data.player_to_play== BLACK) return black_eval;
    else return white_eval;
}
long long int pieces_84(Board &b){
    long long black_eval=0;
    long long white_eval=0;
    if(!(b.data.b_bishop== DEAD)) {
        {
            black_eval+=300;
            white_eval-=300;
        }
    }
    if(!(b.data.b_rook_1== DEAD)) {
        black_eval+=500;
        white_eval-=499;
    }
    if(!(b.data.b_rook_2== DEAD)) {
        black_eval+=500;
        white_eval-=499;
    }
    if(!(b.data.b_pawn_1== DEAD)) {
        if(b.data.b_pawn_1== BISHOP) {
            black_eval+=300;
            white_eval-=300;
        }
        else if (b.data.b_pawn_1== ROOK) {
            black_eval+=500;
            white_eval-=499;
        }
        else {
            black_eval+=90;
            white_eval-=89;
        }
    }
    if(!(b.data.b_pawn_2== DEAD)) {
        if(b.data.b_pawn_2== BISHOP) {
            black_eval+=300;
            white_eval-=300;
        }
        else if (b.data.b_pawn_2== ROOK) {
            black_eval+=500;
            white_eval-=499;
        }
        else  {
            black_eval+=90;
            white_eval-=89;
        }
    }
    if(!(b.data.b_pawn_3== DEAD)) {
        if(b.data.b_pawn_3== BISHOP) {
            black_eval+=300;
            white_eval-=300;
        }
        else if (b.data.b_pawn_3== ROOK) {
            black_eval+=500;
            white_eval-=499;
        }
        else {
            black_eval+=90;
            white_eval-=89;
        }
    }
    if(!(b.data.b_pawn_4== DEAD)) {
        if(b.data.b_pawn_4== BISHOP) {
            black_eval+=300;
            white_eval-=300;
        }
        else if (b.data.b_pawn_4== ROOK) {
            black_eval+=500;
            white_eval-=499;
        }
        else  {
            black_eval+=90;
            white_eval-=89;
        }
    }

    if(!(b.data.w_bishop == DEAD)) {
        white_eval+=300;
        black_eval-=300;
    }
    if(!(b.data.w_rook_1== DEAD)) {
        white_eval+=500;
        black_eval-=499;
    } 
    if(!(b.data.w_rook_2== DEAD))  {
        white_eval+=500;
        black_eval-=499;
    }
    if(!(b.data.w_pawn_1 == DEAD)) {
        if(b.data.w_pawn_1 == BISHOP) {
            white_eval+=300;
            black_eval-=300;
        }
        else if (b.data.w_pawn_1 == ROOK) {
            white_eval+=500;
            black_eval-=499;
        }
        else {
            white_eval+=90;
            black_eval-=80;
        }
    }
    if(!(b.data.w_pawn_2== DEAD)) {
        if(b.data.w_pawn_2== BISHOP) {
            white_eval+=300;
            black_eval-=300;
        }
        else if (b.data.w_pawn_2== ROOK) {
            white_eval+=500;
            black_eval-=499;
        }
        else {
            white_eval+=90;
            black_eval-=80;
        }
    }
    if(!(b.data.w_pawn_3== DEAD)) {
        if(b.data.w_pawn_3== BISHOP) {
            white_eval+=300;
            black_eval-=300;
        }
        else if (b.data.w_pawn_3== ROOK) {
            white_eval+=500;
            black_eval-=499;
        }
        else {
            white_eval+=90;
            black_eval-=80;
        }
    }
    if(!(b.data.w_pawn_4== DEAD)) {
        if(b.data.w_pawn_4== BISHOP) {
            white_eval+=300;
            black_eval-=300;
        }
        else if (b.data.w_pawn_4== ROOK) {
            white_eval+=500;
            black_eval-=499;
        }
        else {
            white_eval+=90;
            black_eval-=80;
        }
    }
    
    if (b.data.player_to_play== BLACK) return black_eval;
    else return white_eval;
}
long long int pieces_82(Board& b){
    long long black_eval=0;
    long long white_eval=0;
    if(!(b.data.b_bishop== DEAD)) {
        {
            black_eval+=300;
            white_eval-=300;
        }
    }
    if(!(b.data.b_knight_1== DEAD)) {
        {
            black_eval+=400;
            white_eval-=399;
        }
    }
    if(!(b.data.b_knight_2== DEAD)) {
        {
            black_eval+=400;
            white_eval-=399;
        }
    }
    if(!(b.data.b_rook_1== DEAD)) {
        black_eval+=500;
        white_eval-=499;
    }
    if(!(b.data.b_rook_2== DEAD)) {
        black_eval+=500;
        white_eval-=499;
    }
    if(!(b.data.b_pawn_1== DEAD)) {
        if(b.data.b_pawn_1== BISHOP) {
            black_eval+=300;
            white_eval-=300;
        }
        else if (b.data.b_pawn_1== ROOK) {
            black_eval+=500;
            white_eval-=499;
        }
        else {
            black_eval+=90;
            white_eval-=89;
        }
    }
    if(!(b.data.b_pawn_2== DEAD)) {
        if(b.data.b_pawn_2== BISHOP) {
            black_eval+=300;
            white_eval-=300;
        }
        else if (b.data.b_pawn_2== ROOK) {
            black_eval+=500;
            white_eval-=499;
        }
        else  {
            black_eval+=90;
            white_eval-=89;
        }
    }
    if(!(b.data.b_pawn_3== DEAD)) {
        if(b.data.b_pawn_3== BISHOP) {
            black_eval+=300;
            white_eval-=300;
        }
        else if (b.data.b_pawn_3== ROOK) {
            black_eval+=500;
            white_eval-=499;
        }
        else  {
            black_eval+=90;
            white_eval-=89;
        }
    }
    if(!(b.data.b_pawn_4== DEAD)) {
        if(b.data.b_pawn_4== BISHOP) {
            black_eval+=300;
            white_eval-=300;
        }
        else if (b.data.b_pawn_4== ROOK) {
            black_eval+=500;
            white_eval-=499;
        }
        else  {
            black_eval+=90;
            white_eval-=89;
        }
    }
    if(!(b.data.w_bishop == DEAD)) {
        white_eval+=300;
        black_eval-=300;
    }
    if(!(b.data.w_rook_1== DEAD)) {
        white_eval+=500;
        black_eval-=499;
    } 
    if(!(b.data.w_knight_1== DEAD)) {
        white_eval+=400;
        black_eval-=399;
    } 
    if(!(b.data.w_knight_2== DEAD)) {
        white_eval+=400;
        black_eval-=399;
    } 
    if(!(b.data.w_rook_2== DEAD))  {
        white_eval+=500;
        black_eval-=499;
    }
    if(!(b.data.w_pawn_1 == DEAD)) {
        if(b.data.w_pawn_1 == BISHOP) {
            white_eval+=300;
            black_eval-=300;
        }
        else if (b.data.w_pawn_1 == ROOK) {
            white_eval+=500;
            black_eval-=499;
        }
        else {
            white_eval+=90;
            black_eval-=80;
        }
    }
    if(!(b.data.w_pawn_2== DEAD)) {
        if(b.data.w_pawn_2== BISHOP) {
            white_eval+=300;
            black_eval-=300;
        }
        else if (b.data.w_pawn_2== ROOK) {
            white_eval+=500;
            black_eval-=499;
        }
        else {
            white_eval+=90;
            black_eval-=80;
        }
    }
    if(!(b.data.w_pawn_3== DEAD)) {
        if(b.data.w_pawn_3== BISHOP) {
            white_eval+=300;
            black_eval-=300;
        }
        else if (b.data.w_pawn_3== ROOK) {
            white_eval+=500;
            black_eval-=499;
        }
        else {
            white_eval+=90;
            black_eval-=80;
        }
    }
    if(!(b.data.w_pawn_4== DEAD)) {
        if(b.data.w_pawn_4== BISHOP) {
            white_eval+=300;
            black_eval-=300;
        }
        else if (b.data.w_pawn_4== ROOK) {
            white_eval+=500;
            black_eval-=499;
        }
        else {
            white_eval+=90;
            black_eval-=80;
        }
    }
    if (b.data.player_to_play== BLACK) return black_eval;
    else return white_eval;
}
long long int util_73   (Board &b){
    long long black_eval=0,white_eval=0;

    if(!(b.data.b_bishop== DEAD)) {
        black_eval+=300;
        white_eval-=300;
    }

    if(!(b.data.b_rook_1== DEAD)) {
        {
            black_eval+=500;
            white_eval-=499;
        }
        if(b.data.player_to_play==BLACK)black_eval+=brook1[6-gety(b.data.b_rook_1)][getx(b.data.b_rook_1)];
    }
    if(!(b.data.b_rook_2== DEAD)) {
        {
            black_eval+=500;
            white_eval-=499;
        }
        if(b.data.player_to_play==BLACK)black_eval+=brook1[6-gety(b.data.b_rook_2)][getx(b.data.b_rook_2)];
    }
    if(!(b.data.b_pawn_1== DEAD)) {
        if(b.data.b_pawn_1== BISHOP) {
            black_eval+=300;
            white_eval-=300;
        }
        else if (b.data.b_pawn_1== ROOK) {
            {
                black_eval+=500;
                white_eval-=499;
            }
            if(b.data.player_to_play==BLACK)black_eval+=brook1[6-gety(b.data.b_pawn_1)][getx(b.data.b_pawn_1)];
        }
        else {
            if(b.data.player_to_play==BLACK){
                black_eval+=bp1[6-gety(b.data.b_pawn_1)][getx(b.data.b_pawn_1)];
            }
            {
                black_eval+=90;
                white_eval-=89;
            }
        }
    }
    if(!(b.data.b_pawn_2== DEAD)) {
        if(b.data.b_pawn_2== BISHOP) {
            black_eval+=300;
            white_eval-=300;
        }
        else if (b.data.b_pawn_2== ROOK){
            {
                black_eval+=500;
                white_eval-=499;
            }
            if(b.data.player_to_play==BLACK)black_eval+=brook1[6-gety(b.data.b_pawn_2)][getx(b.data.b_pawn_2)];
        }
        else {
            if(b.data.player_to_play==BLACK){
                black_eval+=bp1[6-gety(b.data.b_pawn_2)][getx(b.data.b_pawn_2)];
            }
            {
                black_eval+=90;
                white_eval-=89;
            }
        }
    }

    
    if(!(b.data.w_bishop == DEAD)) {
        white_eval+=300;
        black_eval-=300;
    }
    if(!(b.data.w_rook_1== DEAD)) {
        {
            white_eval+=500;
            black_eval-=499;
        }
        if(b.data.player_to_play==WHITE)white_eval+=wrook1[6-gety(b.data.w_rook_1)][getx(b.data.w_rook_1)];
    }
    if(!(b.data.w_rook_2== DEAD)) {
        {
            white_eval+=500;
            black_eval-=499;
        }
        if(b.data.player_to_play==WHITE)white_eval+=wrook1[6-gety(b.data.w_rook_2)][getx(b.data.w_rook_2)];
    }
    if(!(b.data.w_pawn_1 == DEAD)) {
        if(b.data.w_pawn_1 == BISHOP) {
            white_eval+=300;
            black_eval-=300;
        }
        else if (b.data.w_pawn_1 == ROOK){
            {
                white_eval+=500;
                black_eval-=499;
            }
            if(b.data.player_to_play==WHITE)white_eval+=wrook1[6-gety(b.data.w_pawn_1)][getx(b.data.w_pawn_1)];
        }
        else {
            if(b.data.player_to_play==WHITE){
                white_eval+=wp1[6-gety(b.data.w_pawn_1)][getx(b.data.w_pawn_1)];
            }
            white_eval+=90;
            black_eval-=89;
        }
    }
    if(!(b.data.w_pawn_2== DEAD)) {
        if(b.data.w_pawn_2== BISHOP) {
            white_eval+=300;
            black_eval-=300;
        }
        else if (b.data.w_pawn_2== ROOK){
            {
                white_eval+=500;
                black_eval-=499;
            }
            if(b.data.player_to_play==WHITE)white_eval+=wrook1[6-gety(b.data.w_pawn_2)][getx(b.data.w_pawn_2)];
        }
        else {
            if(b.data.player_to_play==WHITE){
                white_eval+=wp1[6-gety(b.data.w_pawn_2)][getx(b.data.w_pawn_2)];
            }
            white_eval+=90;
            black_eval-=89;
        }
    }
    
    
    // if(b.in_check()){
    //     black_eval-=80;
    //     white_eval-=80;
    // }
    if(b.data.player_to_play==WHITE) {
        return white_eval;
    }
    else return black_eval;        
    
}
long long int util_84(Board& b){
    long long black_eval=0,white_eval=0;

    if(!(b.data.b_bishop== DEAD)) {
        black_eval+=300;
        white_eval-=300;
    }

    if(!(b.data.b_rook_1== DEAD)) {
        {
            black_eval+=500;
            white_eval-=499;
        }
        if(b.data.player_to_play==BLACK)black_eval+=brook2[7-gety(b.data.b_rook_1)][getx(b.data.b_rook_1)];
    }
    if(!(b.data.b_rook_2== DEAD)) {
        {
            black_eval+=500;
            white_eval-=499;
        }
        if(b.data.player_to_play==BLACK)black_eval+=brook2[7-gety(b.data.b_rook_2)][getx(b.data.b_rook_2)];
    }
    if(!(b.data.b_pawn_1== DEAD)) {
        if(b.data.b_pawn_1== BISHOP) {
            black_eval+=300;
            white_eval-=300;
        }
        else if (b.data.b_pawn_1== ROOK) {
            {
                black_eval+=500;
                white_eval-=499;
            }
            if(b.data.player_to_play==BLACK)black_eval+=brook2[7-gety(b.data.b_pawn_1)][getx(b.data.b_pawn_1)];
        }
        else {
            if(b.data.player_to_play==BLACK){
                black_eval+=bp2[7-gety(b.data.b_pawn_1)][getx(b.data.b_pawn_1)];
            }
            {
                black_eval+=70;
                white_eval-=70;
            }
        }
    }
    if(!(b.data.b_pawn_2== DEAD)) {
        if(b.data.b_pawn_2== BISHOP) {
            black_eval+=300;
            white_eval-=300;
        }
        else if (b.data.b_pawn_2== ROOK){
            {
                black_eval+=500;
                white_eval-=499;
            }
            if(b.data.player_to_play==BLACK)black_eval+=brook2[7-gety(b.data.b_pawn_2)][getx(b.data.b_pawn_2)];
        }
        else {
            if(b.data.player_to_play==BLACK){
                black_eval+=bp2[7-gety(b.data.b_pawn_2)][getx(b.data.b_pawn_2)];
            }
            {
                black_eval+=70;
                white_eval-=70;
            }
        }
    }
    if(!(b.data.b_pawn_3== DEAD)) {
        if(b.data.b_pawn_3== BISHOP) {
            black_eval+=300;
            white_eval-=300;
        }
        else if (b.data.b_pawn_3== ROOK){
            {
                black_eval+=500;
                white_eval-=499;
            }
            if(b.data.player_to_play==BLACK)black_eval+=brook2[7-gety(b.data.b_pawn_3)][getx(b.data.b_pawn_3)];
        }
        else {
            if(b.data.player_to_play==BLACK){
                black_eval+=bp2[7-gety(b.data.b_pawn_3)][getx(b.data.b_pawn_3)];
            }
            {
                black_eval+=60;
                white_eval-=60;
            }
        }
    }
    if(!(b.data.b_pawn_4== DEAD)) {
        if(b.data.b_pawn_4== BISHOP) {
            black_eval+=300;
            white_eval-=300;
        }
        else if (b.data.b_pawn_4== ROOK){
            {
                black_eval+=500;
                white_eval-=499;
            }
            if(b.data.player_to_play==BLACK)black_eval+=brook2[7-gety(b.data.b_pawn_4)][getx(b.data.b_pawn_4)];
        }
        else {
            if(b.data.player_to_play==BLACK){
                black_eval+=bp2[7-gety(b.data.b_pawn_4)][getx(b.data.b_pawn_4)];
            }
            {
                black_eval+=60;
                white_eval-=60;
            }
        }
    }
    
    if(!(b.data.w_bishop == DEAD)) {
        white_eval+=300;
        black_eval-=300;
    }
    if(!(b.data.w_rook_1== DEAD)) {
        {
            white_eval+=500;
            black_eval-=499;
        }
        if(b.data.player_to_play==WHITE)white_eval+=wrook2[7-gety(b.data.w_rook_1)][getx(b.data.w_rook_1)];
    }
    if(!(b.data.w_rook_2== DEAD)) {
        {
            white_eval+=500;
            black_eval-=499;
        }
        if(b.data.player_to_play==WHITE)white_eval+=wrook2[7-gety(b.data.w_rook_2)][getx(b.data.w_rook_2)];
    }
    if(!(b.data.w_pawn_1 == DEAD)) {
        if(b.data.w_pawn_1 == BISHOP) {
            white_eval+=300;
            black_eval-=300;
        }
        else if (b.data.w_pawn_1 == ROOK){
            {
                white_eval+=500;
                black_eval-=499;
            }
            if(b.data.player_to_play==WHITE)white_eval+=wrook2[7-gety(b.data.w_pawn_1)][getx(b.data.w_pawn_1)];
        }
        else {
            if(b.data.player_to_play==WHITE){
                white_eval+=wp2[7-gety(b.data.w_pawn_1)][getx(b.data.w_pawn_1)];
            }
            white_eval+=70;
            black_eval-=70;
        }
    }
    if(!(b.data.w_pawn_2== DEAD)) {
        if(b.data.w_pawn_2== BISHOP) {
            white_eval+=300;
            black_eval-=300;
        }
        else if (b.data.w_pawn_2== ROOK){
            {
                white_eval+=500;
                black_eval-=499;
            }
            if(b.data.player_to_play==WHITE)white_eval+=wrook2[7-gety(b.data.w_pawn_2)][getx(b.data.w_pawn_2)];
        }
        else {
            if(b.data.player_to_play==WHITE){
                white_eval+=wp2[7-gety(b.data.w_pawn_2)][getx(b.data.w_pawn_2)];
            }
            white_eval+=70;
            black_eval-=70;
        }
    }
    if(!(b.data.w_pawn_3 == DEAD)) {
        if(b.data.w_pawn_3 == BISHOP) {
            white_eval+=300;
            black_eval-=300;
        }
        else if (b.data.w_pawn_3 == ROOK){
            {
                white_eval+=500;
                black_eval-=499;
            }
            if(b.data.player_to_play==WHITE)white_eval+=wrook2[7-gety(b.data.w_pawn_3)][getx(b.data.w_pawn_3)];
        }
        else {
            if(b.data.player_to_play==WHITE){
                white_eval+=wp2[7-gety(b.data.w_pawn_3)][getx(b.data.w_pawn_3)];
            }
            white_eval+=60;
            black_eval-=60;
        }
    }
    if(!(b.data.w_pawn_4== DEAD)) {
        if(b.data.w_pawn_4== BISHOP) {
            white_eval+=300;
            black_eval-=300;
        }
        else if (b.data.w_pawn_4== ROOK){
            {
                white_eval+=500;
                black_eval-=499;
            }
            if(b.data.player_to_play==WHITE)white_eval+=wrook2[7-gety(b.data.w_pawn_4)][getx(b.data.w_pawn_4)];
        }
        else {
            if(b.data.player_to_play==WHITE){
                white_eval+=wp2[7-gety(b.data.w_pawn_4)][getx(b.data.w_pawn_4)];
            }
            white_eval+=60;
            black_eval-=60;
        }
    }
    
    
    // if(b.in_check()){
    //     black_eval-=80;
    //     white_eval-=80;
    // }
    if(b.data.player_to_play==WHITE) {
        return white_eval;
    }
    else return black_eval;        
    
}
long long int util_82(Board& b){ 
    long long black_eval=0,white_eval=0;

    if(!(b.data.b_bishop== DEAD)) {
        black_eval+=300;
        white_eval-=300;
    }
    if(!(b.data.b_knight_1== DEAD)) {
        black_eval+=400;
        white_eval-=399;
    }
    if(!(b.data.b_knight_2== DEAD)) {
        black_eval+=400;
        white_eval-=399;
    }
    if(!(b.data.b_rook_1== DEAD)) {
        {
            black_eval+=500;
            white_eval-=499;
        }
        if(b.data.player_to_play==BLACK)black_eval+=brook3[7-gety(b.data.b_rook_1)][getx(b.data.b_rook_1)];
    }
    if(!(b.data.b_rook_2== DEAD)) {
        {
            black_eval+=500;
            white_eval-=499;
        }
        if(b.data.player_to_play==BLACK)black_eval+=brook3[7-gety(b.data.b_rook_2)][getx(b.data.b_rook_2)];
    }
    if(!(b.data.b_pawn_1== DEAD)) {
        if(b.data.b_pawn_1== BISHOP) {
            black_eval+=300;
            white_eval-=300;
        }
        else if (b.data.b_pawn_1== ROOK) {
            {
                black_eval+=520;
                white_eval-=519;
            }
            if(b.data.player_to_play==BLACK)black_eval+=brook3[7-gety(b.data.b_pawn_1)][getx(b.data.b_pawn_1)];
        }
        else {
            if(b.data.player_to_play==BLACK){
                black_eval+=bp31[7-gety(b.data.b_pawn_1)][getx(b.data.b_pawn_1)];
            }
            {
                black_eval+=50;
                white_eval-=50;
            }
        }
    }
    if(!(b.data.b_pawn_2== DEAD)) {
        if(b.data.b_pawn_2== BISHOP) {
            black_eval+=300;
            white_eval-=300;
        }
        else if (b.data.b_pawn_2== ROOK){
            {
                black_eval+=520;
                white_eval-=519;
            }
            if(b.data.player_to_play==BLACK)black_eval+=brook3[7-gety(b.data.b_pawn_2)][getx(b.data.b_pawn_2)];
        }
        else {
            if(b.data.player_to_play==BLACK){
                black_eval+=bp31[7-gety(b.data.b_pawn_2)][getx(b.data.b_pawn_2)];
            }
            {
                black_eval+=50;
                white_eval-=49;
            }
        }
    }
    if(!(b.data.b_pawn_3== DEAD)) {
        if(b.data.b_pawn_3== BISHOP) {
            black_eval+=300;
            white_eval-=300;
        }
        else if (b.data.b_pawn_3== ROOK){
            {
                black_eval+=520;
                white_eval-=519;
            }
            if(b.data.player_to_play==BLACK)black_eval+=brook3[7-gety(b.data.b_pawn_2)][getx(b.data.b_pawn_2)];
        }
        else {
            if(b.data.player_to_play==BLACK){
                black_eval+=bp3[7-gety(b.data.b_pawn_2)][getx(b.data.b_pawn_2)];
            }
            {
                black_eval+=50;
                white_eval-=49;
            }
        }
    }
    if(!(b.data.b_pawn_4== DEAD)) {
        if(b.data.b_pawn_4== BISHOP) {
            black_eval+=300;
            white_eval-=300;
        }
        else if (b.data.b_pawn_4== ROOK){
            {
                black_eval+=520;
                white_eval-=519;
            }
            if(b.data.player_to_play==BLACK)black_eval+=brook3[7-gety(b.data.b_pawn_2)][getx(b.data.b_pawn_2)];
        }
        else {
            if(b.data.player_to_play==BLACK){
                black_eval+=bp3[7-gety(b.data.b_pawn_2)][getx(b.data.b_pawn_2)];
            }
            {
                black_eval+=50;
                white_eval-=49;
            }
        }
    }
    if(!(b.data.w_bishop == DEAD)) {
        white_eval+=300;
        black_eval-=300;
    }
    if(!(b.data.w_knight_1 == DEAD)) {
        white_eval+=400;
        black_eval-=399;
    }
    if(!(b.data.w_knight_2 == DEAD)) {
        white_eval+=400;
        black_eval-=399;
    }
    if(!(b.data.w_rook_1== DEAD)) {
        {
            white_eval+=500;
            black_eval-=499;
        }
        if(b.data.player_to_play==WHITE)white_eval+=wrook3[7-gety(b.data.w_rook_1)][getx(b.data.w_rook_1)];
    }
    if(!(b.data.w_rook_2== DEAD)) {
        {
            white_eval+=500;
            black_eval-=499;
        }
        if(b.data.player_to_play==WHITE)white_eval+=wrook3[7-gety(b.data.w_rook_2)][getx(b.data.w_rook_2)];
    }
    if(!(b.data.w_pawn_1 == DEAD)) {
        if(b.data.w_pawn_1 == BISHOP) {
            white_eval+=300;
            black_eval-=300;
        }
        else if (b.data.w_pawn_1 == ROOK){
            {
                white_eval+=520;
                black_eval-=519;
            }
            if(b.data.player_to_play==WHITE)white_eval+=wrook3[7-gety(b.data.w_pawn_1)][getx(b.data.w_pawn_1)];
        }
        else {
            if(b.data.player_to_play==WHITE){
                white_eval+=wp31[7-gety(b.data.w_pawn_1)][getx(b.data.w_pawn_1)];
            }
            white_eval+=50;
            black_eval-=49;
        }
    }
    if(!(b.data.w_pawn_2== DEAD)) {
        if(b.data.w_pawn_2== BISHOP) {
            white_eval+=300;
            black_eval-=300;
        }
        else if (b.data.w_pawn_2== ROOK){
            {
                white_eval+=520;
                black_eval-=519;
            }
            if(b.data.player_to_play==WHITE)white_eval+=wrook3[7-gety(b.data.w_pawn_2)][getx(b.data.w_pawn_2)];
        }
        else {
            if(b.data.player_to_play==WHITE){
                white_eval+=wp31[7-gety(b.data.w_pawn_2)][getx(b.data.w_pawn_2)];
            }
            white_eval+=50;
            black_eval-=49;
        }
    }
    if(!(b.data.w_pawn_3== DEAD)) {
        if(b.data.w_pawn_3== BISHOP) {
            white_eval+=300;
            black_eval-=300;
        }
        else if (b.data.w_pawn_3== ROOK){
            {
                white_eval+=520;
                black_eval-=519;
            }
            if(b.data.player_to_play==WHITE)white_eval+=wrook3[7-gety(b.data.w_pawn_2)][getx(b.data.w_pawn_2)];
        }
        else {
            if(b.data.player_to_play==WHITE){
                white_eval+=wp3[7-gety(b.data.w_pawn_2)][getx(b.data.w_pawn_2)];
            }
            white_eval+=50;
            black_eval-=49;
        }
    }
    if(!(b.data.w_pawn_4== DEAD)) {
        if(b.data.w_pawn_4== BISHOP) {
            white_eval+=300;
            black_eval-=300;
        }
        else if (b.data.w_pawn_4== ROOK){
            {
                white_eval+=520;
                black_eval-=519;
            }
            if(b.data.player_to_play==WHITE)white_eval+=wrook3[7-gety(b.data.w_pawn_2)][getx(b.data.w_pawn_2)];
        }
        else {
            if(b.data.player_to_play==WHITE){
                white_eval+=wp3[7-gety(b.data.w_pawn_2)][getx(b.data.w_pawn_2)];
            }
            white_eval+=50;
            black_eval-=49;
        }
    }
    // if(b.in_check()){
    //     black_eval-=80;
    //     white_eval-=80;
    // }
    if(b.data.player_to_play==WHITE) {
        return white_eval;
    }else return black_eval;  
}

long long int utility(Board &b){
    if(b.data.board_type == SEVEN_THREE){
       return util_73(b);
    }else if(b.data.board_type == EIGHT_FOUR){
        return util_84(b);
    }else if(b.data.board_type == EIGHT_TWO){
        return util_82(b);
    }
}
long long int pieces(Board &b){
    if(b.data.board_type == SEVEN_THREE){
       return pieces_73(b);
    }else if(b.data.board_type == EIGHT_FOUR){
        return pieces_84(b);
    }else if(b.data.board_type == EIGHT_TWO){
        return pieces_82(b);
    }
}

void dfs(int plr2play,Node* root, Board b,int curr_depth){
    currentTime = chrono::steady_clock::now();
    elapsedTime = chrono::duration_cast<chrono::milliseconds>(currentTime - startTime).count();
    // if(elapsedTime>=timeLimit) return;
    if(plr2play==0){
        if(curr_depth==root->depth){
            b.do_move_(root->key);
            if(b.get_legal_moves().size()==0){
                if(b.in_check()) root->value=-100000;
                else root->value=0; //count pieces ka func daaldena idhr
                // root->value+=pieces(b);
                root->alpha=root->value;
            }
            else{
                root->value=utility(b);
                root->alpha=root->value;
            }
            return;
        }
        root->value=LONG_LONG_MIN;
        if(root->depth>0) b.do_move_(root->key);
        auto possible_moves = b.get_legal_moves();
        if(possible_moves.size()==0){
            if(b.in_check()) root->value=-100000;
            else root->value=0;
            // root->value+=pieces(b);
            return;
        }
        for(auto u : possible_moves){
            Node* kid = new Node();
            kid->alpha = root->alpha;
            kid->beta = root->beta;
            kid->key = u;
            kid->depth = root->depth+1;
            // if(kid->alpha>=kid->beta) break;
            dfs(1,kid,b,curr_depth);
            if(root->value<kid->value){
                root->value=kid->value;
                root->state=kid->key;
                root->alpha = max(root->alpha,root->value);
            }
            if(root->alpha>=root->beta) break;

        }
        
    }
    //opponent
    else{
        if(curr_depth==root->depth){
            b.do_move_(root->key);
            if(b.get_legal_moves().size()==0){
                if(b.in_check()) root->value=100000;
                else root->value=0; //count pieces ka func daaldena idhr
                // root->value+=pieces(b);
                root->beta=root->value;
            }
            else{
                root->value=utility(b);
                root->beta=root->value;
            }
            return;
        }
        root->value=LONG_LONG_MAX;
        if(root->depth>0) b.do_move_(root->key);
        auto possible_moves = b.get_legal_moves();
        if(possible_moves.size()==0){
            if(b.in_check()) root->value=100000*(curr_depth+1-root->depth);
            else root->value=0; //count pieces ka func daaldena idhr
            // root->value+=pieces(b);
            return;
        }
        for(auto u : possible_moves){
            Node* kid = new Node();
            kid->alpha = root->alpha;
            kid->beta = root->beta;
            kid->key = u;
            kid->depth = root->depth+1;
            // if(kid->alpha>=kid->beta) break;
            dfs(0,kid,b,curr_depth);
            if(root->value>kid->value){
                root->value=kid->value;
                root->state=kid->key;
                root->beta = min(root->beta,root->value);
            }
            if(root->alpha>=root->beta) break;
           
        }
    }
}
void Engine::find_best_move(const Board& b) {
    startTime = chrono::steady_clock::now();
    timeLimit=(int)chrono::duration_cast<chrono::milliseconds>(this->time_left).count()-100;

    auto moveset = b.get_legal_moves();
    // for(auto u:moveset){
    //     cout<<u<<" ";
    // }
    // cout<<"\n";
    if (moveset.size() == 0) {
        this->best_move = 0;
    }else {
        Tree star= Tree(); 
        Node* root = star.root;
        
        if(b.data.board_type==SEVEN_THREE){
            if((this->time_left).count()<70000) dfs(0,root,b,4);
            else dfs(0,root,b,6);
        }else if(b.data.board_type==EIGHT_FOUR){
            if((this->time_left).count()<130000) dfs(0,root,b,4);
            else dfs(0,root,b,6);
        }else{
            dfs(0,root,b,4);     
            
        }
        
        vector<U16> moves;
        moveset.clear();
        moveset.insert(root->state);
        sample(
            moveset.begin(),
            moveset.end(),
            back_inserter(moves),
            1,
            mt19937{random_device{}()}
        );
        this->best_move = moves[0];    
    }
}