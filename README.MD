# Overview
`Kibot`은 강원중학교 안내 로봇입니다.

[Kibot Homepage](https://tdh8316.github.io/Kibot/)

## Project structure
    .
    ├── client          # Kibot client for Android
    ├── core            # Kibot core implemented with Arduino
    │   ├── robot       # Kibot body
    ├── docs            # Kibot web site
    ├── tests           # Test files
    └── README.md       

## 교실 갱신 요청하기
Kibot client 은 애플리케이션 인스턴스가 시작될 때 마다 `client/share/classinfo.json` 에서 교실 정보를 불러옵니다.
`classinfo.json` 은 다음과 같은 구조입니다:

```json
{
  "101": "엄재훈 선생님",
  "102": "황은경 선생님",
  "103": "교무실"
}
```

모든 위젯은 동적으로 갱신되지는 않지만 다음 실행시부터 변경 사항이 반영됩니다.

교실이 변경되었을 때 `client/share/classinfo.json`를 알맞게 수정해 `update request` label 을 붙여 issue를 작성하거나 이메일 (tdh8316@naver.com) 등을 이용해 연락을 취해주세요.
