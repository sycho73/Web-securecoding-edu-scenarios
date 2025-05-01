# Web-securecoding-edu-scenarios

0.실습 환경 구성 방법<br><br>
1)WSL 설치 (윈도우 환경에선 실습에서 진행하고자 하는 보안 기법인 DEP, ASLR이 자동 적용되어있기에 Linux OS에서 하는게 좋음)<br>
$ wsl --install<br><br>
2)Ubuntu 터미널에서 기본 세팅<br>
$sudo apt update<br>
$sudo apt install build-essential gdb<br><br>
3)소스코드 작성 후 gcc로 컴파일(-no -pie는 Position Independent Executable를 꺼서 ASLR 약화, -fno-stack-protector를 통해 스택 프로텍터 끔 -> 스택 버퍼 오버플로우 보호 제거거, -Wno-implicit-function-declaration을 통해 컴파일할 때 경고 무시 후 강제 컴파일일)<br>
$gcc -o order order.c -no-pie -fno-stack-protector -Wno-implicit-function-declaration<br><br>
4)ASLR 끄기(루트 권한 필요)<br>
$sudo sysctl -w kernel.randomize_va_space=0<br>
4-1)실습 이후 kernel.randomize_va_space=2로 복구하기<br><br>

0.5. VSCode for Window환경에서 할시<br>
1)확장 -> Remote WSL(2025.04.30기준 WSL)<br>
2)code .<br><br>

1.Apache 서버 실행<br>
1)서버 처음 시작할 때<br>
$sudo service apache2 start<br><br>
1-1)http://localhost 로 연결 확인가능(Apache는 기본적으로 80포트 사용)<br>
1-2)http://localhost/web/insert.html 실제 웹 페이지를 보여주고 싶으면 경로도 지정해주면됨<br><br>
2)서버 실행 중이며 변경 적용 시<br>
PHP 설정(php.ini), Apache 설정(apache2.conf), 새로운 모듈 설치할 때만 사용<br>
$sudo service apache2 restart<br><br>
3)서버 종료<br>
$sudo service apache2 stop<br><br>

1.5.심볼릭 링크로 작업공간하고 링크하여 /var/www/html에서 실행하기<br>
1)심볼릭 링크를 이용하여 VScode작업공간하고 링크하여 실시간으로 참조하게 하기<br>
$sudo ln -s /mnt/c/Users/user/Desktop/Git\ 작업\ 공간/Web-securecoding-edu-scenarios /var/www/html<br>
2)확인한 ip로 접속 http://localhost/web/insert.html <br><br>

2.공격 확인 테스트<br>
1)backend폴더 안에 있는 order.c 파일을 컴파일<br>
$make<br><br>
2)이후 서버 실행 중 변경 후 http://localhost/web/insert.html 에 들어가서 테스트<br><br>
3)Integer Overflow test<br>
주문수량에 2147484 입력<br>
⚠️ Integer Overflow 발생!(총 가격에서 발생)<br>
요청 수량: 2147484 <br>
단가: 2000원 <br>
총 가격: 704원 <br>
⚠️ Integer Overflow로 인해 실제 계산된 수량: 0 (원래 입력: 2147484)<br>
나올 시 성공적인 테스트<br><br>
4)Integer Overflow->Buffer Overflow test<br>
주문수량에 4294967296+n 입력 및 특별상품 개수에 k값 입력(이 때 n은 양의 정수이며 k값은 n이상의 양의 정수 값)<br>
⚠️ Integer Overflow 발생!(주문 수량에서 발생)<br>
요청 수량: n<br>
단가: 2000원<br>
총 가격: n*2000원<br>
⚠️ Buffer Overflow 발생 가능성! (특별상품 버퍼 크기보다 더 많이 저장 시도)<br>
특별상품 ID 저장 완료 (실제로 요청된 수량: n, 실제 저장된 개수: n)<br>
나올 시 성공적인 테스트<br>
4-1)여기에선 실제 Buffer Overflow가 발생하진 않고 논리적인 의미에서의 시나리오 가능성 체크<br><br>
5)Buffer Overflow test<br>
추가요구사항에 문자열의 길이가 20을 넘는(a가 21개) 문자열 입력<br>
⚠️ 추가 요구사항 입력 길이 초과 (Buffer Overflow 가능성)<br>
추가 요청사항: aaaaaaaaaaaaaaaaaaaaa<br>
5-1)여기 또한 실제 Buffer Overflow가 발생하진 않고 논리적인 의미에서의 시나리오 가능성 체크. 해당 부분은 실제 공격을 통해 공격 결과 출력 예정<br><br>

3.실제 공격<br>
0)공격 시나리오 : Integer Overflow, Integer Overflow -> Buffer Overflow, Buffer Overflow<br>
1)Integer Overflow : 총 가격(주문수량x2000)에 Integer Overflow를 일으킬 주문수량값을 입력하여 총 가격 정보 변조<br>
1-1) 2.공격 확인 테스트-3) Integer Overflow test 과정과 동일하게 진행<br><br>
2)Integer Overflow -> Buffer Overflow : 주문수량에 Integer Overflow를 일으킬 주문수량값을 입력하고 주문수량 중 특별상품(특별상품은 각자 고유의 ID를 가지는 상품으로 ID 정보 저장을 위해 최대 주문수량 만큼 가능하기에 주문수량 크기만큼 할당)으로 업그레이드 시킬 제품 수량을 Integer Overflow에 의해 작아진 Buffer크기를 넘어 Buffer Overflow를 일으킬 특별상품 수량값을 입력하여 실제로 할당되는 크기 변조<br>
2-1) 2.공격 확인 테스트-4) Integer Overflow->Buffer Overflow test 과정과 동일하게 진행<br><br>
3)Buffer Overflow test : 




