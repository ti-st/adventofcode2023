      * day1_1
       identification division.
           program-id. boot-race.
           author. kayms.
      *
       data division.



           working-storage section.


           01 r_index pic 9(9).
           01 race_times.
               02 t pic 9(15) occurs 4 times.

           01 distances.
               02 d pic 9(15) occurs 4 times.

           01 t_p pic 9(9).
           01 t_m pic 9(9).

           01 ws-sum pic 9(9).

       procedure division.

           move 000000000000040 to t(1).
           move 000000000000070 to t(2).
           move 000000000000098 to t(3).
           move 000000000000079 to t(4).
           move 000000000000215 to d(1).
           move 000000000001051 to d(2).
           move 000000000002147 to d(3).
           move 000000000001005 to d(4).
           move 1 to r_index.
           move 1 to ws-sum.

           perform varying  r_index from 1 by 1 until r_index > 4
               perform calc_rance
           end-perform.

           display "sum " ws-sum.

           move 000000040709879 to race_times.
           move 215105121471005 to distances.
           move 1 to r_index.
           move 1 to ws-sum.

           perform calc_rance.

           display "sum part 2 " ws-sum.

           stop run.

       calc_rance.
           compute t_m = t(r_index)/2 -
           function sqrt((t(r_index)*t(r_index) / 4) - d(r_index)).
           compute t_p = t(r_index)/2 +
           function sqrt((t(r_index)*t(r_index) / 4) - d(r_index)).
           compute t_p = t_p - t_m.
           compute ws-sum = ws-sum * t_p.
