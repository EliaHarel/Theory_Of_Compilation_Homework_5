
function run_all_tests {
  if [ ! -f $exe_path ]; then
    echo "Executable file is not found!"
    exit
  fi
  echo "Start."
  for var in {1..25};
  do
    if [ ! -f t${var}.in ]; then
      continue
    fi
    echo -n "running test #$var ... "
    ./hw5 < t${var}.in 2>&1 > t${var}.ll
    lli t${var}.ll > t${var}_my.out
    diff t${var}.out t${var}_my.out &> /dev/null
    if [[ $? != 0 ]]
    then
      echo "Failed!"
      sleep 1
      #   vimdiff t${var}.out t${var}_my.out
      #  exit
    else echo "ok"
    fi
  done

}

# if [ "$#" -ne 1 ]; then
# echo "Illegal number of parameters. Must be 1."
# exit
# fi

make
cp hw5 hw5Yehonatan/

cd hw5Yehonatan

run_all_tests hw5
