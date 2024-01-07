## Guess the Number:

Bạn có thể tạo một trò chơi "Đoán số" đơn giản, trong đó máy tính sẽ tạo ra một số ngẫu nhiên và người chơi phải đoán số đó. Dưới đây là một phác thảo cơ bản của trò chơi:

1. Máy tính tạo ra một số ngẫu nhiên từ 0 đến 99.
2. Người chơi được yêu cầu đoán số.
3. Nếu số đoán của người chơi cao hơn hoặc thấp hơn số thực, trò chơi sẽ cung cấp một gợi ý.
4. Người chơi tiếp tục đoán cho đến khi họ đoán đúng số.
5. Sau khi người chơi đoán đúng số, trò chơi sẽ hiển thị số lần cố gắng mà họ đã thực hiện.

```cpp
#include "iostream"
#include <cstdlib>
#include <ctime>

using namespace std;

class Guess {
   private:
    int numRandom = 0;

   public:
    int genNum() {
        srand(static_cast<unsigned int>(time(nullptr)));  // Seed the random number generator
        int numRandom = rand() % 100;                     // Generate a random number between 0 and 99
        // cout << "Random number: " << numRandom << endl;
        return numRandom;
    }

    void guessNum(int numberRandom) {
        int numGuess;
        // int numRandom = genNum();
        cout << "*Insert your lucky number: ";
        cin >> numGuess;
        // check
        while (numGuess != numberRandom) {
            if (numGuess > numberRandom) {
                cout << "Incorrect, it's \033[1;31msmaller\033[0m than you guessed" << endl;
            } else {
                cout << "Incorrect, it's \033[1;31mbigger\033[0m than you guessed" << endl;
            }
            cout << "*Insert your lucky number: ";
            cin >> numGuess;
        }
        cout << "\033[1;32mExactly!\033[0m" << endl;
    }
};

int main() {
    Guess guessNumber;
    int numberGenarate = guessNumber.genNum();
    // cout << "value: " << numberGenarate << endl;
    guessNumber.guessNum(numberGenarate);
    return 0;
}
```

## Manager task:

1. Tạo một lớp Task với các thuộc tính như tên công việc, ngày hết hạn và trạng thái.
2. Thực hiện chức năng:

- tạo ra task mới: tên task là unique
- xóa công việc: xóa theo tên task, theo status của task hoặc theo ngày (quá khứ/tương lai)
- thay đổi dữ liệu của task
- lưu trữ dữ liệu được nhập vào 1 file chỉ định
- hiển thị 'all task' trong 1 file đc lưu trữ chỉ định

Lưu ý: các case nhập sai cần được phát triển để cảnh báo tới người dùng.
