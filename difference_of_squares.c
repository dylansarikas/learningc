unsigned int sum_of_squares(unsigned int number)
{
    unsigned int ans=0, i;
    for (i = 1; i <= number; i++) {
        ans += i*i;
    }
    return ans;
}

unsigned int square_of_sum(unsigned int number){
    unsigned int ans=0, i;
    for (i = 1; i <= number; i++) {
        ans += i;
    }
    ans = ans * ans;
    return ans;
}

unsigned int difference_of_squares(unsigned int number){
    unsigned int sum_first=0, square_first=0, ans;
    sum_first = square_of_sum(number);
    square_first = sum_of_squares(number);
    ans = sum_first - square_first;
    return ans;
}
