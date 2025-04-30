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
5)심볼릭 링크로 연결, 이걸 안하면 파일을 수정할 때마다 /var/www/html에 직접 복사해줘야하기 때문<br>
$sudo rm -rf /var/www/html/*<br>
$sudo ln -s "~작업공간/web" /var/www/html<br><br><br>

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

2.공격 테스트<br>
1)backend폴더 안에 있는 order.c 파일을 컴파일<br>
$make<br><br>
2)이후 http://localhost/web/insert.html 에 들어가서 테스트<br><br>
3)Integer Overflow test<br>
Quantity에 4294967295-> 4294966296 나올 시 성공적인 테스트<br><br>
4)Buffer Overflow test<br>



