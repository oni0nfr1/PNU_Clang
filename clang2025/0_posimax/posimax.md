# 코드
```c
#include <stdio.h>

int main() {
    int N, new, max = 0;
    scanf("%d" ,&N);
    while(N--) {
        scanf("%d" ,&new);
        max = max > new ? max : new;
    }
    max ? printf("%d" ,max) : printf("None");
}
```
# 해설
N회에 걸쳐서 정수들을 입력받은 뒤, 양수 중 가장 큰 것을 출력하거나, 양수가 없었다면 None을 출력하면 되므로 N회에 걸쳐서 new에 새 정수들을 읽어온 뒤 max와 비교하여 max보다 크면 new를 max로 덮어쓰는 방식으로 구현하면 됩니다.

## Tip
* max의 값 초기화는 0 이하의 어떤 정수로 해도 상관이 없습니다. 받은 정수들 중에 양수가 없었다면 max 역시 양수가 아닐 테니 마지막에 max > 0을 통해 None을 출력해야 하는지를 구별할 수 있고 만약 0으로 초기화했다면 위 코드와 같이 0과의 비교 연산을 하지 않고 조건문에 max만 써도 됩니다.
<br>
* C++에는 max 함수가 있어 최댓값을 구할 때 max(new, max)를 반복하는 방식으로 깔끔하게 작성할 수 있으나 C에는 max 함수가 없습니다. 대신 위처럼 삼항연산자를 이용하면 깔끔하게 쓸 수 있습니다.
<br>
* 사실 위의 코드는 가독성보다는 토큰을 줄이는 것을 목표로 하여 작성했습니다. 좀더 깔끔하게
```c
#include <stdio.h>

int main() {
    int N, new, max = 0;
    scanf("%d" ,&N);
    
    for(int i = 0 ; i < N ; i++) {
        scanf("%d" ,&new);
        max = max > new ? max : new;
    }
    
    if(max == 0) printf("None");
    else         printf("%d" ,max);
    
    return 0;
}
```
와 같이 쓰는 것이 좋다고 봅니다.