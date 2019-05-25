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
    ../test/default.txt ../test/default.log empty_list

bash ../test/single_test.sh ../test/empty_map.csv ../test/default.lst \
    ../test/default.txt ../test/default.log empty_map

bash ../test/single_test.sh ../test/default.csv ../test/invalid_dir.lst \
    ../test/default.txt ../test/default.log invalid_dir

bash ../test/single_test.sh ../test/default.csv ../test/invalid_dist.lst \
    ../test/default.txt ../test/default.log invalid_dist

bash ../test/single_test.sh ../test/default.csv ../test/no_space.lst \
    ../test/default.txt ../test/default.log no_space_list

#test invalid map
bash ../test/single_test.sh ../test/incorrect_rows.csv ../test/default.lst \
    ../test/default.txt ../test/default.log incorrect_rows

bash ../test/single_test.sh ../test/incorrect_cols.csv ../test/default.lst \
    ../test/default.txt ../test/default.log incorrect_cols

bash ../test/single_test.sh ../test/negative_cols.csv ../test/default.lst \
    ../test/default.txt ../test/default.log negative_cols

bash ../test/single_test.sh ../test/invalid_rows.csv ../test/default.lst \
    ../test/default.txt ../test/default.log invalid_rows

bash ../test/single_test.sh ../test/invalid_treasure_type.csv ../test/default.lst \
    ../test/default.txt ../test/default.log invalid_treasure_type

bash ../test/single_test.sh ../test/invalid_slot.csv ../test/default.lst \
    ../test/default.txt ../test/default.log invalid_slot

bash ../test/single_test.sh ../test/invalid_value.csv ../test/default.lst \
    ../test/default.txt ../test/default.log invalid_value

bash ../test/single_test.sh ../test/too_many_colons.csv ../test/default.lst \
    ../test/default.txt ../test/default.log too_many_colons

bash ../test/single_test.sh ../test/too_little_colons.csv ../test/default.lst \
    ../test/default.txt ../test/default.log too_little_colons

bash ../test/single_test.sh ../test/no_space.csv ../test/default.lst \
    ../test/default.txt ../test/default.log no_space_map
