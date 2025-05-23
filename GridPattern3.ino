#define ROW1 13
#define ROW2 12
#define ROW3 11
#define ROW4 10
#define ROW5 9
#define ROW6 8
#define ROW7 7
#define ROW8 6

#define COL1 5
#define COL2 4
#define COL3 3
#define COL4 A4
#define COL5 A3
#define COL6 A2
#define COL7 A1
#define COL8 A0

const int row[] = { ROW1, ROW2, ROW3, ROW4, ROW5, ROW6, ROW7, ROW8 };
const int col[] = { COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8 };

byte pattern[8][8];  // 存放目前圖形資料

void setup() {
  for (byte i = 0; i < 8; i++) {
    pinMode(row[i], OUTPUT);
    pinMode(col[i], OUTPUT);
  }

  Serial.begin(9600);
}

void loop() {
  // 從 Processing 接收資料
  if (Serial.available() >= 8) {
    for (int i = 0; i < 8; i++) {
      byte b = Serial.read();
      for (int j = 0; j < 8; j++) {
        pattern[i][j] = (b >> (7 - j)) & 0x01;
      }
    }
  }

  showPattern(pattern);
}

void showPattern(byte matrix[8][8]) {
  for (byte i = 0; i < 8; i++) {
    // 先關閉所有行列
    for (byte k = 0; k < 8; k++) {
      digitalWrite(row[k], HIGH);
      digitalWrite(col[k], LOW);
    }

    // 啟用目前列
    digitalWrite(row[i], LOW);

    // 設定每個欄位的狀態
    for (byte j = 0; j < 8; j++) {
      if (matrix[i][j] == 1) {
        digitalWrite(col[j], HIGH);
      }
    }

    delay(1); // 控制掃描速度（越小越亮）
  }
}

