//题目:给定一个n次多项式的系数和给定一个m次多项式的系数,求它们的卷积
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 3000005;
//const double PI = 3.141592653589793238462643383279502884197169399375105820974944;
const double PI =acos(-1);
ll mod = (ll) 998244353;
int n,m;
struct Complex{
    double x,y;
    Complex operator+(const Complex& t)const{
        return {x+t.x,y+t.y};
    }
    Complex operator-(const Complex& t)const{
        return {x-t.x,y-t.y};
    }
    Complex operator*(const Complex& t)const{
        return {x*t.x-y*t.y,x*t.y+y*t.x};
    }
}tree[N],ans[N];
int rev[N],bit,tot;
void fft(Complex a[],int inv){
    //每个点二进制只反转一次
    for(int i=0;i<tot;i++)if(i<rev[i])swap(a[i],a[rev[i]]);

    for(int mid=1;mid<tot;mid<<=1){

        auto w1=Complex({cos(PI/mid),inv*sin(PI/mid)});

        for(int i=0;i<tot;i+=(mid*2)){

            auto wk=Complex({1,0});
            for(int j=0;j<mid;j++,wk=wk*w1){

                auto x=a[i+j],y=wk*a[i+j+mid];

                a[i+j]=x+y,a[i+j+mid]=x-y;
            }

        }
    }
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;i++)scanf("%lf",&tree[i].x);
    for(int i=0;i<=m;i++)scanf("%lf",&ans[i].x);
    while((1<<bit)<(n+m+1))bit++;
    tot=(1<<bit);
    for(int i=0;i<tot;i++){
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
    }
    fft(tree, 1);fft(ans, 1);
    for(int i=0;i<tot;i++){
        tree[i]= tree[i] * ans[i];
    }
    fft(tree, -1);
    for(int i=0;i<=(n+m);i++){
        printf("%d ",(int)(tree[i].x / tot + 0.5));
    }
    return 0;
}
