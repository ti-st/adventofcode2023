      * day5_1
       identification division.
           program-id. seeds.
           author. kayms.
      *
       environment division.
           input-output section.
           file-control.
           select f-input assign to "../input.txt"
           organization is line sequential.

       data division.
           file section.

           fd f-input.
           01 input_line pic x(300).

           working-storage section.

           01 seeds.
               02 seed pic 9(9) occurs 21 times indexed by i.

           01 destinations.
               02 dest pic 9(12) occurs 21 times indexed by j.

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

           01 ws-transf pic 9(12).

           01 ws-found pic 9.

           01 ws-seed_temp pic x(200).
           01 ws-temp_c pic x(200).

           01 ws-sum pic 9(10).
           01 ws-eof pic a(1).

           01 dest_range pic 9(12).
           01 src_range pic 9(12).
           01 range_len pic 9(12).

           01 ws-first_line pic 9 value 1.

           01 tmp_nr pic 9(12).

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
      * check mode
                       evaluate true
                           when is_sts
                               move dest_range to sts_dest_index(ws-i)
                               move src_range to sts_src_index(ws-i)
                               move range_len to sts_len(ws-i)
                           when is_stf
                               move dest_range to stf_dest_index(ws-i)
                               move src_range to stf_src_index(ws-i)
                               move range_len to stf_len(ws-i)
                           when is_ftw
                               move dest_range to ftw_dest_index(ws-i)
                               move src_range to ftw_src_index(ws-i)
                               move range_len to ftw_len(ws-i)
                           when is_wtl
                               move dest_range to wtl_dest_index(ws-i)
                               move src_range to wtl_src_index(ws-i)
                               move range_len to wtl_len(ws-i)
                           when is_ltt
                               move dest_range to ltt_dest_index(ws-i)
                               move src_range to ltt_src_index(ws-i)
                               move range_len to ltt_len(ws-i)
                           when is_tth
                               move dest_range to tth_dest_index(ws-i)
                               move src_range to tth_src_index(ws-i)
                               move range_len to tth_len(ws-i)
                           when is_htl
                               move dest_range to htl_dest_index(ws-i)
                               move src_range to htl_src_index(ws-i)
                               move range_len to htl_len(ws-i)
                           when other
                               move "search" to r_mode
                       end-evaluate
                   end-if
               else
                   move "search" to r_mode
               end-if

      *         display y-num(1)

           end-perform.

      *     display soil_to_fertilizer_map.
      *     display fertilizer-to-water_map.
      *     display water-to-light_map.
      *     display light-to-temperature_map.
      *     display temperature-to-humidity_map.
      *     display humidity-to-location_map.

           perform get_index_sts.

           sort dest on ascending.
           display destinations.
           display dest(2).

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
           perform varying ws-i from 1 by 1 until ws-i > 300

               if ws-seed_temp(ws-i:1) = space then
                   move tmp_nr to seed(i)
                   add 1 to i
                   move 0 to tmp_nr
               else
                   move  function numval(ws-seed_temp(ws-i:1)) to ws-j
		           compute tmp_nr = tmp_nr * 10 + ws-j
               end-if
           end-perform.

           display "seeds " seeds.

       get_index_sts.
           set i to 1.

           perform varying i from 1 by 1 until seed(i) = 0
               display "seed "seed(i)
               move 0 to ws-found
               perform varying ws-i from 1 by 1 until ws-i > 200
                   compute ws-k = seed(i) - sts_src_index(ws-i)
                   if ws-k >= 0 and ws-k <= sts_len(ws-i) then
                       compute ws-transf = ws-k + sts_dest_index(ws-i)
                       perform get_index_stf
                   end-if
               end-perform
               if ws-found not = 1 then
                   move seed(i) to ws-transf
                   perform get_index_stf
               end-if
           end-perform.

       get_index_stf.
           display "trans " ws-transf
           perform varying ws-j from 1 by 1 until ws-j > 200
               compute ws-k = ws-transf - stf_src_index(ws-j)
               if ws-k >= 0 and ws-k <= stf_len(ws-j) then
                   compute ws-transf = ws-k + stf_dest_index(ws-j)
                   perform get_index_ftw
                   exit paragraph
               end-if
           end-perform

           perform get_index_ftw.

       get_index_ftw.
           display "trans " ws-transf
           perform varying ws-j from 1 by 1 until ws-j > 200
               compute ws-k = ws-transf - ftw_src_index(ws-j)
               if ws-k >= 0 and ws-k <= ftw_len(ws-j) then
                   compute ws-transf = ws-k + ftw_dest_index(ws-j)
                   perform get_index_wtl
                   exit paragraph
               end-if
           end-perform

           perform get_index_wtl.

       get_index_wtl.
           display "trans " ws-transf
           perform varying ws-j from 1 by 1 until ws-j > 200
               compute ws-k = ws-transf - wtl_src_index(ws-j)
               if ws-k >= 0 and ws-k <= wtl_len(ws-j) then
                   compute ws-transf = ws-k + wtl_dest_index(ws-j)
                   perform get_index_ltt
                   exit paragraph
               end-if
           end-perform

           perform get_index_ltt.

       get_index_ltt.
           display "trans " ws-transf
           perform varying ws-j from 1 by 1 until ws-j > 200
               compute ws-k = ws-transf - ltt_src_index(ws-j)
               if ws-k >= 0 and ws-k <= ltt_len(ws-j) then
                   compute ws-transf = ws-k + ltt_dest_index(ws-j)
                   perform get_index_tth
                   exit paragraph
               end-if
           end-perform

           perform get_index_tth.

       get_index_tth.
           display "trans " ws-transf
           perform varying ws-j from 1 by 1 until ws-j > 200
               compute ws-k = ws-transf - tth_src_index(ws-j)
               if ws-k >= 0 and ws-k <= tth_len(ws-j) then
                   compute ws-transf = ws-k + tth_dest_index(ws-j)
                   perform get_index_htl
                   exit paragraph
               end-if
           end-perform.

           perform get_index_htl.

       get_index_htl.
           display "trans " ws-transf
           perform varying ws-j from 1 by 1 until ws-j > 200
               compute ws-k = ws-transf - htl_src_index(ws-j)
               if ws-k >= 0 and ws-k <= htl_len(ws-j) then
                   compute ws-transf = ws-k + htl_dest_index(ws-j)
                   display "dest " ws-transf " index " i
                   move ws-transf to dest(i)
                   move 1 to ws-found
                   exit paragraph
               end-if
           end-perform

           display "dest " ws-transf.
           move ws-transf to dest(i)
           move 1 to ws-found.
