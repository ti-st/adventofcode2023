      * day5_2
       identification division.
           program-id. seeds_ranges.
           author. kayms.
      *
       environment division.
           input-output section.
           file-control.
           select f-input assign to "../testInput.txt"
           organization is line sequential.

       data division.
           file section.

           fd f-input.
           01 input_line pic x(300).

           working-storage section.

           01 seeds.
               02 seed pic 9(12) occurs 22 times indexed by i.

           01 seeds_ranges.
               02 seed_range occurs 11 times.
                   03 seed_start pic 9(12).
                   03 seed_len pic 9(12).


           01 range_min pic 9(12) value 9999999999.

           01 rangers.
               02 ranger occurs 50000 times indexed by k.
                   03 ranger_start pic 9(12).
                   03 ranger_end pic 9(12).

           01 rangers-copy.
               02 ranger-copy occurs  50000 times indexed by k-c.
                   03 ranger_start_copy pic 9(12).
                   03 ranger_end_copy pic 9(12).

           01 all_input_ranges.
               02 input_ranges occurs 8 times.
                   03 input_range occurs 200 times.
                       04 i_start pic 9(12).
                       04 i_end pic 9(12).
                       04 m_start pic 9(12).
                       04 m_end pic 9(12).

           01 seed_to_soil_map.
               02 seed_to_soil occurs 200 times.
                   03 sts_src_index pic 9(12).
                   03 sts_dest_index pic 9(12).
                   03 sts_len pic 9(12).


           01 soil_to_fertilizer_map.
               02 soil_to_fertilizer occurs 200 times.
                   03 stf_src_index pic 9(12).
                   03 stf_dest_index pic 9(12).
                   03 stf_len pic 9(12).

           01 fertilizer-to-water_map.
               02 fertilizer-to-water occurs 200 times.
                   03 ftw_src_index pic 9(12).
                   03 ftw_dest_index pic 9(12).
                   03 ftw_len pic 9(12).

           01 water-to-light_map.
               02 water-to-light occurs 200 times.
                   03 wtl_src_index pic 9(12).
                   03 wtl_dest_index pic 9(12).
                   03 wtl_len pic 9(12).

           01 light-to-temperature_map.
               02 light-to-temperature occurs 200 times.
                   03 ltt_src_index pic 9(12).
                   03 ltt_dest_index pic 9(12).
                   03 ltt_len pic 9(12).

           01 temperature-to-humidity_map.
               02 temperature-to-humidity occurs 200 times.
                   03 tth_src_index pic 9(12).
                   03 tth_dest_index pic 9(12).
                   03 tth_len pic 9(12).


           01 humidity-to-location_map.
               02 humidity-to-location occurs 200 times.
                   03 htl_src_index pic 9(12).
                   03 htl_dest_index pic 9(12).
                   03 htl_len pic 9(12).



           01 ws-i pic 9(12).
           01 ws-j pic S9(12).
           01 ws-k pic S9(12).
           01 ws-l pic 9(12).
           01 ws-m pic 9(12).

           01 ws-ranger-index pic 9(12).

           01 ws-curr_seed pic 9(12).

           01 ws-transf pic 9(12).

           01 ws-found pic 9.

           01 ws-seed_temp pic x(200).
           01 ws-temp_c pic x(200).

           01 ws-sum pic 9(10).
           01 ws-eof pic a(1).

           01 dest_range pic 9(12).
           01 src_range pic 9(12).
           01 range_len pic 9(12).

           01 ws-curr_map_index pic 999 value 1.

           01 ws-first_line pic 9 value 1.

           01 tmp_nr pic 9(12).

           01 shift pic S9(12).

           01 r_mode pic x(80) value "search".

           01 maps pic x(80).
               88 is_sts value "seed-to-soil map:".
               88 is_stf value "soil-to-fertilizer map:".
               88 is_ftw value "fertilizer-to-water map:".
               88 is_wtl value "water-to-light map:".
               88 is_ltt value "light-to-temperature map:".
               88 is_tth value "temperature-to-humidity map:".
               88 is_htl value "humidity-to-location map:".


       procedure division.

           open input f-input.
           perform until ws-eof = 'Y'
               read f-input into input_line at
               end move 'Y' to ws-eof
               not at end

               if ws-first_line = 1 then
                   move 0 to ws-first_line
                   perform read_seed_nums
               end-if

               if input_line(1:1) not = space then
                   if r_mode = "search" then
                       move input_line to maps
                       move input_line to r_mode
                       move 0 to ws-i
                   else
      * read values
                       add 1 to ws-i
                       unstring input_line delimited by space
                           into dest_range, src_range, range_len
                       end-unstring
                       compute ws-m = src_range + range_len
                       compute ws-l = dest_range + range_len
      * check mode
                       evaluate true
                           when is_sts
                               move dest_range to sts_dest_index(ws-i)
                               move src_range to sts_src_index(ws-i)
                               move range_len to sts_len(ws-i)
                               display " src " src_range
                               " dest " dest_range
                               " ws-m " ws-m
                               " ws-l " ws-l
                               move src_range to i_start(1,ws-i)
                               move ws-m to i_end(1, ws-i)
                               move dest_range to m_start(1,ws-i)
                               move ws-l to m_end(1,ws-i)
                           when is_stf
                               move dest_range to stf_dest_index(ws-i)
                               move src_range to stf_src_index(ws-i)
                               move range_len to stf_len(ws-i)

                               move src_range to i_start(2,ws-i)
                               move ws-m to i_end(2, ws-i)
                               move dest_range to m_start(2,ws-i)
                               move ws-l to m_end(2,ws-i)
                           when is_ftw
                               move dest_range to ftw_dest_index(ws-i)
                               move src_range to ftw_src_index(ws-i)
                               move range_len to ftw_len(ws-i)

                               move src_range to i_start(3,ws-i)
                               move ws-m to i_end(3, ws-i)
                               move dest_range to m_start(3,ws-i)
                               move ws-l to m_end(3,ws-i)
                           when is_wtl
                               move dest_range to wtl_dest_index(ws-i)
                               move src_range to wtl_src_index(ws-i)
                               move range_len to wtl_len(ws-i)

                               move src_range to i_start(4,ws-i)
                               move ws-m to i_end(4, ws-i)
                               move dest_range to m_start(4,ws-i)
                               move ws-l to m_end(4,ws-i)
                           when is_ltt
                               move dest_range to ltt_dest_index(ws-i)
                               move src_range to ltt_src_index(ws-i)
                               move range_len to ltt_len(ws-i)

                               move src_range to i_start(5,ws-i)
                               move ws-m to i_end(5, ws-i)
                               move dest_range to m_start(5,ws-i)
                               move ws-l to m_end(5,ws-i)
                           when is_tth
                               move dest_range to tth_dest_index(ws-i)
                               move src_range to tth_src_index(ws-i)
                               move range_len to tth_len(ws-i)

                               move src_range to i_start(6,ws-i)
                               move ws-m to i_end(6, ws-i)
                               move dest_range to m_start(6,ws-i)
                               move ws-l to m_end(6,ws-i)
                           when is_htl
                               move dest_range to htl_dest_index(ws-i)
                               move src_range to htl_src_index(ws-i)
                               move range_len to htl_len(ws-i)

                               move src_range to i_start(7,ws-i)
                               move ws-m to i_end(7, ws-i)
                               move dest_range to m_start(7,ws-i)
                               move ws-l to m_end(7,ws-i)
                           when other
                               move "search" to r_mode
                       end-evaluate
                   end-if
               else
                   move "search" to r_mode
               end-if

      *         display y-num(1)

           end-perform.

           perform to_seed_ranges.

      *     perform split_rangers_sts.

      *     display soil_to_fertilizer_map.
      *     display fertilizer-to-water_map.
      *     display water-to-light_map.
      *     display light-to-temperature_map.
      *     display temperature-to-humidity_map.
      *     display humidity-to-location_map.


      *     sort dest on ascending.
      *     display destinations.
      *     display dest(2).

           perform varying ws-curr_map_index from 1 by 1 until
               ws-curr_map_index > 7
               display ws-curr_map_index
               perform varying ws-i from 1 by 1 until
                   i_end(ws-curr_map_index, ws-i) = 0

                   display "in range "
                   i_start(ws-curr_map_index, ws-i) " to "
                   i_end(ws-curr_map_index, ws-i)" | "
                   m_start(ws-curr_map_index,ws-i) " to "
                   m_end(ws-curr_map_index, ws-i)

               end-perform


           end-perform.


           perform varying ws-curr_map_index from 1 by 1 until
               ws-curr_map_index > 7

               perform copy_ranges_into_copy_ranges
           end-perform.

      *     sort ranger_start ascending.
           perform varying  ws-i from 1 by 1 until ws-i > 50000

      *         display ranger_start(ws-i)

           end-perform.

           display "range min " range_min.

           display "sum " ws-sum.

           close f-input.
           stop run.

       read_seed_nums.
           set i to 1.
           unstring input_line delimited by ':'
               into ws-temp_c, ws-seed_temp
           end-unstring.

           move function trim(ws-seed_temp) to ws-seed_temp.

           move 0 to tmp_nr.
           perform varying ws-i from 1 by 1 until ws-i > 199 or i > 20
               if ws-seed_temp(ws-i:1) = space then
                   move tmp_nr to seed(i)
                   add 1 to i
                   move 0 to tmp_nr
               else
                   move  function numval(ws-seed_temp(ws-i:1)) to ws-j
		           compute tmp_nr = tmp_nr * 10 + ws-j
               end-if
           end-perform.

      *     display "seeds " seeds.

       to_seed_ranges.
           set i to 1.
           set k to 1.
           perform varying i from 2 by 2 until seed(i) = 0
               move seed(i - 1) to ranger_start(k)
               compute ranger_end(k) = seed(i) + seed(i - 1)
      *         display "seed range "
      *         ranger_start(k) " to " ranger_end(k)
               add seed_len(k) to ws-sum
               add 1 to k
           end-perform.


       split_rangers_sts.
      *     display k.
      *     perform varying ws-i from 1 by 1 until sts_len(ws-i) = 0
      *         perform varying  ws-j from 1 by until ws-j > k

      *         end-perform
      *     end-perform.



      * copy ranges into copy ranges
      * clear ranges
      * add new ranges into copy ranges
      * check for overlaps -> put new ranges into ranges
      * clear ranges-copy


       copy_ranges_into_copy_ranges.

           perform varying ws-i from 1 by 1 until ranger_end(ws-i) = 0
               move ranger_start(ws-i) to ranger_start_copy(ws-i)
               move ranger_end(ws-i) to ranger_end_copy(ws-i)
               move ws-i to ws-j
           end-perform.

           perform clear_ranges.

       clear_ranges.

           perform varying ws-i from 1 by 1 until ws-i > 500
               move 0 to ranger_start(ws-i)
               move 0 to ranger_end(ws-i)
           end-perform.
           move 1 to ws-ranger-index.

           perform form_new_ranges.

       form_new_ranges.

           display " "
           perform varying ws-i from 1 by 1
            until ws-i > ws-j

               display "curr range " ranger_start_copy(ws-i) " to "
               ranger_end_copy(ws-i)

               perform varying ws-k from 1 by 1
               until i_end(ws-curr_map_index, ws-k) = 0
      * overlap fall 1
                   display "try range " i_start(ws-curr_map_index, ws-k)
                   " to " i_end(ws-curr_map_index, ws-k)

                   if i_start(ws-curr_map_index, ws-k)
                       >= ranger_start_copy(ws-i)
                       and i_end(ws-curr_map_index, ws-k)
                       < ranger_end_copy(ws-i)
                       then
      * new range

                           move m_start(ws-curr_map_index, ws-k)
                           to ranger_start(ws-ranger-index)

                           if i_end(ws-curr_map_index, ws-k)
                               < ranger_end_copy(ws-ranger-index)
                               then

                               compute ranger_end(ws-ranger-index) =
                               m_end(ws-curr_map_index, ws-k)

                           else

                               compute ranger_end(ws-ranger-index) =
                               ranger_end_copy(ws-i)
                               - i_end(ws-curr_map_index, ws-k)
                               + m_start(ws-curr_map_index, ws-k)

                           end-if
      * new ranges from orgin TODO

                           display "1 add new range "
                           ranger_start(ws-ranger-index) " to "
                           ranger_end(ws-ranger-index)


                           add 1 to ws-ranger-index

      * reduce first range
                           move i_start(ws-curr_map_index, ws-k)
                           to ranger_end(ws-i)

                   end-if
      * overlap fall 2

                   if ranger_start_copy(ws-i)
                       >= i_start(ws-curr_map_index, ws-k)
                       and ranger_start_copy(ws-i)
                       < i_end(ws-curr_map_index, ws-k)
                       then

                       compute ranger_start(ws-ranger-index)
                       = ranger_start_copy(ws-i)
                       - i_start(ws-curr_map_index, ws-k)
                       + m_start(ws-curr_map_index, ws-k)

                       if ranger_end_copy(ws-ranger-index)
                           < i_end(ws-curr_map_index, ws-k)
                           then

                           compute shift
                           = m_start(ws-curr_map_index, ws-k)
                           - i_start(ws-curr_map_index, ws-k)

                           compute ranger_end(ws-ranger-index) =
                           ranger_end_copy(ws-ranger-index) + shift
                       else

                           move m_end(ws-curr_map_index, ws-k)
                           to ranger_end(ws-ranger-index)
                       end-if

                       display "2 add new range "
                       ranger_start(ws-ranger-index) " to "
                       ranger_end(ws-ranger-index)

                       add 1 to ws-ranger-index

                   end-if
               end-perform

           end-perform.

           perform  copy_left_overs_back.

       copy_left_overs_back.

      *     display " "
      *     perform varying ws-i from 1 by 1
      *         until ws-i >= ws-ranger-index
      *             display "range " ranger_start(ws-i)
      *             " to " ranger_end(ws-i)
      *     end-perform.

           display " index " ws-ranger-index.
           perform varying ws-i from 1 by 1
               until ranger_end_copy(ws-i) = 0

               move ranger_start_copy(ws-i)
               to ranger_start(ws-ranger-index)

               move ranger_end_copy(ws-i)
               to ranger_end(ws-ranger-index)

               add 1 to ws-ranger-index

           end-perform

           perform clear_ranges_copy.

           display " "
           display " after step"
           perform varying ws-i from 1 by 1
               until ws-i >= ws-ranger-index
                   display "range " ranger_start(ws-i)
                   " to " ranger_end(ws-i)

                   if ranger_start(ws-i) < range_min
                       and ranger_start(ws-i) > 0 then
                       move ranger_start(ws-i) to range_min
                   end-if
           end-perform.

       clear_ranges_copy.

           perform varying ws-i from 1 by 1
               until ws-i > 500
               move 0 to ranger_start_copy(ws-i)
               move 0 to ranger_end_copy(ws-i)
           end-perform.
