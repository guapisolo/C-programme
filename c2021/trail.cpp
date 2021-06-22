int dfs(int now)
{
    if( checkwinner() ) return winner_value*now;
    int ma=-inf, tmp;
    for( all available positions )
    {
        place_piece();
        tmp = -dfs(-now);
        ma = max(ma,tmp);
    }
    return ma;
}
ll AlphaBeta(int dep,int now,int Alpha,int Beta)
{
    ll threat, ma=-inf, tmp; 
    Play piece[N1*N1]; memset(piece,0,sizeof(piece)); int pcnt=0;
    //malloc
    int tx=0,ty=0;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(!cur[dep-1].a[i][j]) 
    {
        memcpy(mp,cur[dep-1].a,sizeof(mp)); mp[i][j]=now;
        threat = assess::totMap(now,-now);
        if(threat>ma) tx = i, ty = j;
        ma = max(ma,threat); 
        // if( threat <= -anxt[3]+eps || threat >= anow[1]-eps )
        // {
        //     if(dep==1) posx = tx, posy = ty;
        //     return ma;
        // }
        piece[++pcnt] = (Play){i,j,threat}; //记录当前落子的估值
    }
    //threat：当前局面评分 越高越好
    //对 对手威胁值 最大 
    sort(piece+1,piece+pcnt+1,cmpmax);
    int id=0;
    if( ma <= -anxt[4]+eps || ma >= anow[2]-eps )
    {
        if(dep==1) posx = tx, posy = ty;
        return ma;
    }
    if(dep==dfs_deep) return ma;
    // if(dep==1) swap(piece[1],piece[4]);
    if(step<8)
    {
        int fl=rand()%4;
        if(fl==0) swap(piece[4],piece[6]), swap(piece[5],piece[7]);
    }
    for(int k=1;k <= bfs_num;k++)
    {
        int i = piece[k].x, j = piece[k].y;
        memcpy(cur[dep].a,cur[dep-1].a,sizeof(mp)); cur[dep].a[i][j]=now;
        tmp = -AlphaBeta(dep+1,-now,-Beta,-Alpha);
        // if(dep==1)
        // {
        //     de=1;
        //     push_inform(i,j,piece[k].val,tmp);
        // }
        if(tmp >= Beta) return Beta;
        if(tmp > Alpha){
            Alpha = tmp;
            id = k;
        } 
    }
    if(dep==1)
    { 
        if(Alpha <= -anxt[4]+eps) id=1;
        posx = piece[id].x; posy = piece[id].y; 
    }
    return Alpha;
}