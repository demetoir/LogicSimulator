# LogicSimulator

오픈소스 논리 회로 시뮬레이터 프로그램 [Logisim](http://www.cburch.com/logisim/)의 클론 코딩 프로젝트

![screenshot](./screenshot_1.jpg)

# 목차

-   개요
-   제작 및 담당 기능 구현
-   데모
-   빌드 환경
-   실행파일 다운로드

## 개요

-   2016 1학기 윈도우 프로그래밍 강좌의 팀 프로젝트
-   학부 과정 수준의 논리 회로를 설계 및 실험 할 수 있는 시뮬레이터
-   [Logisim](http://www.cburch.com/logisim/)의 클론 프로젝트
-   Windows SDK 버전 업데이트로 빌드 후 실행 가능한 수준을 유지함
-   논리회로 시뮬레이션 엔진(`C++(Visual C++)`)과 랜더링 프로그램(`MFC`) 나누어서 설계 및 개발
-   개발 기간: 2016.5.11 ~ 2016.6.9

## 제작자 및 담당 기능 구현

-   김유준([github](https://github.com/demetoir))

    -   논리 회로 시뮬레이션 엔진 구현
    -   기본 논리게이트 랜더링 구현
    -   라이브러리 박스 랜더링 구현
    -   로직 컴포넌트 save/load 구현

-   박성규([github](https://github.com/psk7142))

    -   플립플롭 랜더링 구현
    -   7 segment 랜더링 구현
    -   논리게이트 및 컴포넌트 방향 및 라벨링 구현
    -   이미지 리소스 디자인 및 MFC 스타일 설정

## 데모

### 1. 회로 만들기 및 실행

[![회로 만들기 및 실행 demo 1](http://img.youtube.com/vi/2oZ0oXUksdQ/0.jpg)](http://www.youtube.com/watch?v=2oZ0oXUksdQ "회로 만들기 및 실행 demo 1")

-   링크: http://www.youtube.com/watch?v=2oZ0oXUksdQ

### 2. 만든 회로를 컴포넌트로 저장 및 불러오기

[![회로를 하나의 컴포턴트로 저장 및 로딩 후 실행](http://img.youtube.com/vi/2oZ0oXUksdQ/0.jpg)](http://www.youtube.com/watch?v=2oZ0oXUksdQ "회로를 하나의 컴포턴트로 저장 및 로딩 후 실행")

-   링크: http://www.youtube.com/watch?v=2oZ0oXUksdQ

## 빌드 환경

-   os : Windows 10
-   Windows SDK 10.0.17134.0

## 실행파일 다운로드

[다운로드](https://github.com/demetoir/LogicSimulator/releases)
