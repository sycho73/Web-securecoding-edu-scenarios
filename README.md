# Web-securecoding-edu-scenarios

0.실습 환경 구성 방법<br>
1)WSL 설치 (윈도우 환경에선 실습에서 진행하고자 하는 보안 기법인 DEP, ASLR이 자동 적용되어있기에 Linux OS에서 하는게 좋음)<br>
$ wsl --install<br>
2)Ubuntu 터미널에서 기본 세팅<br>
$sudo apt update<br>
$sudo apt install build-essential gdb<br>
3)소스코드 작성 후 gcc로 컴파일(-no -pie는 Position Independent Executable를 꺼서 ASLR 약화, -fno-stack-protector를 통해 스택 프로텍터 끔 -> 스택 버퍼 오버플로우 보호 제거거, -Wno-implicit-function-declaration을 통해 컴파일할 때 경고 무시 후 강제 컴파일일)<br>
$gcc -o vuln vulnerable_server.c -no-pie -fno-stack-protector -Wno-implicit-function-declaration<br>
4)ASLR 끄기(루트 권한 필요)<br>
$sudo sysctl -w kernel.randomize_va_space=0<br>
4-1)실습 이후 kernel.randomize_va_space=2로 복구하기<br>


