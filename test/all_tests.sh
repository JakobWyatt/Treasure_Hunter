#!\bin\bash

#test valid files
bash ../test/single_test.sh ../test/default.csv ../test/default.lst \
    ../test/default.txt ../test/default.log default

bash ../test/single_test.sh ../test/bounds.csv ../test/bounds.lst \
    ../test/bounds.txt ../test/bounds.log bounds

#Placeholder expected outputs for now
#Invalid file formats
#test invalid list
bash ../test/single_test.sh ../test/default.csv ../test/empty_list.lst \
    ../test/empty_list.txt ../test/empty.log empty_list

bash ../test/single_test.sh ../test/empty_map.csv ../test/default.lst \
    ../test/empty_map.txt ../test/empty.log empty_map

bash ../test/single_test.sh ../test/default.csv ../test/invalid_dir.lst \
    ../test/invalid_dir.txt ../test/empty.log invalid_dir

bash ../test/single_test.sh ../test/default.csv ../test/invalid_dist.lst \
    ../test/invalid_dist.txt ../test/empty.log invalid_dist

bash ../test/single_test.sh ../test/default.csv ../test/no_space.lst \
    ../test/default.txt ../test/empty.log no_space_list

#test invalid map
bash ../test/single_test.sh ../test/incorrect_rows.csv ../test/default.lst \
    ../test/default.txt ../test/empty.log incorrect_rows

bash ../test/single_test.sh ../test/incorrect_cols.csv ../test/default.lst \
    ../test/default.txt ../test/empty.log incorrect_cols

bash ../test/single_test.sh ../test/negative_cols.csv ../test/default.lst \
    ../test/default.txt ../test/empty.log negative_cols

bash ../test/single_test.sh ../test/invalid_rows.csv ../test/default.lst \
    ../test/default.txt ../test/empty.log invalid_rows

bash ../test/single_test.sh ../test/invalid_treasure_type.csv ../test/default.lst \
    ../test/default.txt ../test/empty.log invalid_treasure_type

bash ../test/single_test.sh ../test/invalid_slot.csv ../test/default.lst \
    ../test/default.txt ../test/empty.log invalid_slot

bash ../test/single_test.sh ../test/invalid_value.csv ../test/default.lst \
    ../test/default.txt ../test/empty.log invalid_value

bash ../test/single_test.sh ../test/too_many_colons.csv ../test/default.lst \
    ../test/default.txt ../test/empty.log too_many_colons

bash ../test/single_test.sh ../test/too_little_colons.csv ../test/default.lst \
    ../test/default.txt ../test/empty.log too_little_colons

bash ../test/single_test.sh ../test/no_space.csv ../test/default.lst \
    ../test/default.txt ../test/empty.log no_space_map
