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
