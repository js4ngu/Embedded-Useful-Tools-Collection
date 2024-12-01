#include <Wire.h>

// 상수 정의
const int SERIAL_BITRATE = 9600; // 시리얼 통신 비트레이트
const int SCAN_DELAY_MS = 5000;  // 검색 후 대기 시간(ms)

// 설정 초기화
void setup() {
  Wire.begin(); // I2C 초기화
  Serial.begin(SERIAL_BITRATE); // 시리얼 통신 시작
  while (!Serial); // 시리얼 통신 준비 대기
  Serial.println("\nI2C 스캐너 시작"); // 프로그램 시작 메시지
}

// 메인 루프
void loop() {
  Serial.println("I2C 디바이스를 검색 중입니다...");

  int deviceCount = 0; // 발견된 I2C 디바이스 수

  // I2C 주소 범위를 순회하며 스캔
  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address); // I2C 주소로 통신 시작
    byte error = Wire.endTransmission(); // 통신 결과 반환

    if (error == 0) { // 오류가 없으면 디바이스 발견
      Serial.print("I2C 디바이스 발견: 주소 0x");
      Serial.printf("%02X\n", address); // 16진수 형식으로 출력
      deviceCount++;
    } 
    else if (error == 4) { // 오류 코드 4는 알 수 없는 오류
      Serial.print("알 수 없는 오류 발생: 주소 0x");
      Serial.printf("%02X\n", address);
    }
  }

  // 결과 출력
  if (deviceCount == 0) {
    Serial.println("I2C 디바이스를 찾을 수 없습니다.");
  } else {
    Serial.print("총 발견된 I2C 디바이스: ");
    Serial.println(deviceCount);
  }

  Serial.println("검색 완료\n");
  delay(SCAN_DELAY_MS); // 검색 후 대기
}
