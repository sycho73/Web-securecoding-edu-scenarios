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
4-1)실습 이후 kernel.randomize_va_space=2로 복구하기<br><br><br>

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
$sudo service apache2 stop<br><br><br>

1.5.심볼릭 링크로 작업공간하고 링크하여 /var/www/html에서 실행하기<br>
1)심볼릭 링크를 이용하여 VScode작업공간하고 링크하여 실시간으로 참조하게 하기<br>
$sudo ln -s /mnt/c/Users/user/Desktop/Git\ 작업\ 공간/Web-securecoding-edu-scenarios /var/www/html<br>
2)확인한 ip로 접속 http://localhost/web/insert.html <br><br>

2.공격 확인 테스트<br>
1)backend폴더 안에 있는 order.c 파일을 컴파일<br>
$make<br><br>
2)이후 서버 실행 중 변경 후 http://localhost/web/insert.html 에 들어가서 테스트<br><br>
3)Integer Overflow test<br>
Quantity에 2147484-> ⚠️ Integer Overflow 발생! Total price: 704 나올 시 성공적인 테스트<br><br>
4)3번에서 발생한 Integer Overflow에 의한 Buffer Overflow test<br>

5)Buffer Overflow test<br>
Special Request에 aaaaaaaaaaaaaaaaaaaaa(총 21개)->⚠️ Buffer Overflow 가능성 있음! (입력 길이 초과)Order received: aaaaaaaaaaaaaaaaaaaaa 나올 시 성공적인 테스트(입력 길이 더 길어지면 명령 실행 실패 뜸 현재는 aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa(32개)이상)<br><br><br>

3.실제 공격(Integer Overflow -> Buffer Overflow 시나리오)<br>
0)구체적인 시나리오 : 



