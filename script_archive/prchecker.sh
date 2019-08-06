#!/bin/bash
# Params
max_line_change=50
current_branch_name=$(git branch | grep '*' | sed 's/\*\ \(.*\)/\1/')
master_branch="origin/master"
​
while true; do
  echo -e "$current_branch_name \e[1;42m-branch를 PR하려고 하십니까?\e[0m"
  read -p "[y/n]" yn
  case $yn in
    [Yy]* ) break;;
    [Nn]* ) return;;
    * ) echo "Please answer yes or no.";;
  esac
done
​
git checkout -b tmp
git commit -a -m"commit by prchecker"
​
# Start Check for Pull Request
echo -e "\e[1;42mTest 0) 추가된 코드 숫자 체크 \e[0m"
read -p "[press any]"
​
number_of_added_line=$(git diff $master_branch --shortstat | sed 's/.*,\ \([0-9]\+\)\ insertion.*/\1/')
if [ $number_of_added_line -gt $max_line_change ]
then
  # https://www.shellhacks.com/bash-colors/
  echo -e "\e[1;31m너무 많은 코드수정을 한번에 PR하려 합니다.\e[0;31m $number_of_added_line줄 추가";
else
  echo -e "\e[1;42m적당한 라인수정.\e[0m $number_of_added_line 줄 추가."
fi
while true; do
    echo -e "\e[1;31m계속 PR준비를 진행하겠습니까?\e[0m";
    read -p "[y/n]"
    case $yn in
        [Yy]* ) break;;
        [Nn]* ) return;;
        * ) echo "Please answer yes or no.";;
    esac
done
​
#git diff $master_branch -- '*.cc' '*.cpp' | egrep "^\+"  # Diff for source code only
git diff $master_branch -- '*.c' '*.cc' '*.cpp' | sed -e 's/\(+++\|---\)\ b\(.*\)/\1 b\2\n#########################################################################################/'
​
echo -e "\e[1;42m1) 모든 소스코드(정의)가 주석으로 설명되고 있습니까?\e[0m"
read -p "[press any]" # TODO 몇줄 이상 주석이 없으면 경고표시
​
#git diff $master_branch -- '*.h' '*.hpp' | egrep "^\+"  # Diff for source code only
git diff $master_branch -- '*.h' '*.hpp' | sed 's/\(+++\|---\)\ b\(.*\)/\1 b\2\n########################################################################################/'
echo -e "\e[1;31mWarning! 소스코드의 함수 선언은 체크해주지 않습니다.\e[0m";
echo -e "\e[1;42m1-1) 모든 함수/클래스 선언에 doxygen 스타일 주석이 있습니까?\e[0m"
read -p "[press any]"
echo -e "\e[1;42m2) 모든 변수명/주석이 문법적으로 맞습니까?\e[0m"
read -p "[press any]"
echo -e "\e[1;42m3) 원격 repository에서 빌드테스트(누락파일점검)를 해봤습니까? [press any]\e[0m"  # TODO build test 기능
read -p "[press any]"
echo -e "\e[1;42m4) unit test를 해봤습니까?\e[0m"
read -p "[press any]"
echo -e "\e[1;42m4-1) 모든 코드가 unit test로 커버가 됩니까?\e[0m"
read -p "[press any]"
echo -e "\e[1;42m5) 회사 가이드라인에 따라 함수명을 지었나요?\e[0m" # TODO cpplint을 공부해서 config를 회사 가이드라인에 맞게 하려면 너무 오래걸려서 미룸.
read -p "[press any]"
echo -e "\e[1;42m6) 병합테스트를 실행합니다. (이후 자동으로 원상복구합니다.)\e[0m"
read -p "[press any]"
git checkout master && git merge tmp --no-commit --no-ff -X theirs
git reset --hard $master_branch
echo -e "\e[1;42m병합테스트를 통과했나요?\e[0m"
read -p "[press any]"
git checkout $current_branch_name
git merge tmp --no-commit
# git reset HEAD^1  # Remove commit "commit by prchecker"
git branch -D tmp
