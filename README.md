# myShell Program
리눅스 시스템프로그래밍 마이쉘 프로그램
Linux Systemprogramming myShell program

환경 : Ubuntu / Linux 환경
언어 : C언어

- 기존의 shell과 유사하게 무한 루프를 돌면서, 사용자의 명령을 입력받아, 입력 받은 명령을 child process가 수행하도록 한다.
- parent process는 child process가 종료할 때까지 기다린다.
- 이 프로그램이 수행되는 환경에 관한 내용은 .myshell 파일에 저장되어 있는 것으로 가정한다.
- .myshell 파일에는 PATH=/bin:/usr/bin:/usr/local/bin: 이라고 내용이 저장되어 있다.
- 사용자가 myshell 상에서 "date"라고 입력하면, myShell 프로그램에서는 현재 디렉토리에 있는 .myshell파일에서 PATH를 읽어서 각 경로에 "date"라는 명령이 있는지 확인한다.
- 명령이 있는 경우에 해당 프로그램을 실행한다.

<결과 화면>
![텀프로젝트_결과](https://user-images.githubusercontent.com/90028687/173495373-e0fee161-6d2b-4ccc-84c0-ef22c5fc4659.png)
