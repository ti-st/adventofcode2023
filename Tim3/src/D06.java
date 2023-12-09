import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import utils.InputFile;

class Race{
    long time;
    long distance;
    Race(long time, long distance){
        this.time = time;
        this.distance = distance;
    }
}

public class D06 {
    static List<String> raw;
    static List<Race> races;
    static Race p2Race;
    static void parseInput(){
        raw = InputFile.readFile("./Tim3/src/input/06.txt");
        //raw = InputFile.readFile("./Tim3/src/input/06Sample.txt");
        races = new ArrayList<>();
        Pattern digiPattern = Pattern.compile("(\\d+)");
        Matcher matcher_time = digiPattern.matcher(raw.get(0));
        Matcher matcher_dist = digiPattern.matcher(raw.get(1));
        String p2Time = "";
        String p2Dist = "";
        while (matcher_time.find() && matcher_dist.find()) {
            long time = Long.parseLong(matcher_time.group(0));
            long dist = Long.parseLong(matcher_dist.group(0));
            Race race = new Race(time, dist);
            races.add(race);
            //System.out.prlongln("Race time: "+time+" distance: "+dist);
            p2Time += matcher_time.group(0);
            p2Dist += matcher_dist.group(0);
        }
        p2Race = new Race(Long.parseLong(p2Time), Long.parseLong(p2Dist));

    }

    static long part1(){
        long result = 1;
        for (Race race: races){
            long beats = 0;
            for (long i=0; i<race.time; i++){
                long speed = i;
                long time_left = race.time-i;
                long dist = speed*time_left;
                if (dist > race.distance) beats++;
            }
            result *= beats;
        }

        return result;
    }

    static long part2(){
        long beats = 0;
        for (long i=0; i<p2Race.time; i++){
            long speed = i;
            long time_left = p2Race.time-i;
            long dist = speed*time_left;
            if (dist > p2Race.distance) beats++;
        }

        return beats;

    }

    public static void main(String[] args) {
        parseInput();
        System.out.println("Part 1: "+part1());
        System.out.println("Part 2: "+part2());
    }

}
