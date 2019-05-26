#!\bin\bash

make clean && make

#test valid files
bash ../test/single_test.sh ../test/default.csv ../test/default.lst \
    ../test/default.txt ../test/default.log default

bash ../test/single_test.sh ../test/bounds.csv ../test/bounds.lst \
    ../test/bounds.txt ../test/bounds.log bounds

#Incorrect number of args
rm adventure.log
rm ../test/output.log

echo "Running test incorrect_args"

valgrind --leak-check=full -v --log-file=../test/valgrind1_$5.log --error-exitcode=1 ./TreasureHunter &>> ../test/output.log
if [ $? == 1 ]; then
    echo "Memory error."
fi
valgrind --leak-check=full -v --log-file=../test/valgrind2_$5.log --error-exitcode=1 ./TreasureHunterLog &>> ../test/output.log
if [ $? == 1 ]; then
    echo "Memory error."
fi
valgrind --leak-check=full -v --log-file=../test/valgrind3_$5.log --error-exitcode=1 ./TreasureHunterAI &>> ../test/output.log
if [ $? == 1 ]; then
    echo "Memory error."
fi

cmp --silent ../test/output.log ../test/incorrect_args.txt || echo "Unexpected stdout."


#Placeholder expected outputs for now
#Invalid file formats
#test invalid list
bash ../test/single_test.sh ../test/default.csv ../test/doesnt_exist.lst \
    ../test/list_doesnt_exist.txt ../test/empty.log list_doesnt_exist

bash ../test/single_test.sh ../test/default.csv ../test/empty_list.lst \
    ../test/empty_list.txt ../test/empty.log empty_list

bash ../test/single_test.sh ../test/default.csv ../test/invalid_dir.lst \
    ../test/invalid_dir.txt ../test/empty.log invalid_dir

bash ../test/single_test.sh ../test/default.csv ../test/invalid_dist.lst \
    ../test/invalid_dist.txt ../test/empty.log invalid_dist

#Error message isn't perfect here: doesn't state file name,
#makes it ambiguous whether or not the map or list has an error.
bash ../test/single_test.sh ../test/default.csv ../test/no_space.lst \
    ../test/no_space_list.txt ../test/empty.log no_space_list

bash ../test/single_test.sh ../test/default.csv ../test/negative_dist.lst \
    ../test/negative_dist.txt ../test/empty.log negative_dist

bash ../test/single_test.sh ../test/default.csv ../test/floating_dist.lst \
    ../test/floating_dist.txt ../test/empty.log floating_dist

#test invalid map
bash ../test/single_test.sh ../test/doesnt_exist.csv ../test/default.lst \
    ../test/map_doesnt_exist.txt ../test/empty.log map_doesnt_exist

bash ../test/single_test.sh ../test/empty_map.csv ../test/default.lst \
    ../test/empty_map.txt ../test/empty.log empty_map

bash ../test/single_test.sh ../test/incorrect_rows.csv ../test/default.lst \
    ../test/incorrect_rows.txt ../test/empty.log incorrect_rows

bash ../test/single_test.sh ../test/incorrect_cols.csv ../test/default.lst \
    ../test/incorrect_cols.txt ../test/empty.log incorrect_cols

bash ../test/single_test.sh ../test/negative_cols.csv ../test/default.lst \
    ../test/negative_cols.txt ../test/empty.log negative_cols

bash ../test/single_test.sh ../test/invalid_rows.csv ../test/default.lst \
    ../test/invalid_rows.txt ../test/empty.log invalid_rows

#Row error message is accurate but may be misinterpreted
bash ../test/single_test.sh ../test/invalid_treasure_type.csv ../test/default.lst \
    ../test/invalid_treasure_type.txt ../test/empty.log invalid_treasure_type

#Generic error message - still gives the correct position though
bash ../test/single_test.sh ../test/invalid_slot.csv ../test/default.lst \
    ../test/invalid_slot.txt ../test/empty.log invalid_slot

bash ../test/single_test.sh ../test/invalid_value.csv ../test/default.lst \
    ../test/invalid_value.txt ../test/empty.log invalid_value

bash ../test/single_test.sh ../test/too_many_colons.csv ../test/default.lst \
    ../test/too_many_colons.txt ../test/empty.log too_many_colons

bash ../test/single_test.sh ../test/too_little_colons.csv ../test/default.lst \
    ../test/too_little_colons.txt ../test/empty.log too_little_colons

bash ../test/single_test.sh ../test/no_space.csv ../test/default.lst \
    ../test/no_space_map.txt ../test/empty.log no_space_map
