import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.HashMap;
import java.time.format.DateTimeFormatter;
import java.time.LocalDateTime;

import utils.InputFile;
import utils.Utils;

class Range{
    long start;
    long end;
    long length;
    Range(long start, long end){
        this.start = start;
        this.end = end;
        this.length = end-start;
    }
    // contains start and end
    boolean fullyContains(Range other){
        return this.start <= other.start && this.end >= other.end;
    }
    // contains start but not end
    boolean containsStart(Range other){
        return this.start <= other.start && this.start < other.end && this.end < other.end;
    }
    // contains end but not start
    boolean containsEnd(Range other){
        return other.start < this.start && other.end >= this.start && other.end <= this.end;
    }
    boolean overlaps(Range other){
        return this.start > other.start && this.end < other.end;
    }
    boolean contains(Range other){
        return this.fullyContains(other) || this.containsStart(other) || this.containsEnd(other) || this.overlaps(other);
    }
    List<Range> split(Range other){
        List<Range> ranges = new ArrayList<>();
        if (this.containsStart(other)){
            //System.out.println("containsStart");
            ranges.add(new Range(this.end+1, other.end));
        }
        if (this.containsEnd(other)){
            //System.out.println("containsEnd");
            ranges.add(new Range(other.start, this.start-1));
        }
        if (this.overlaps(other)){
            //System.out.println("overlaps");
            ranges.add(new Range(other.start, this.start-1));
            ranges.add(new Range(this.end+1, other.end));
        }
        if (this.fullyContains(other)){
            //System.out.println("fullyContains");
            ranges.add(new Range(other.start, other.end));
        }
        return ranges;
    }
    public String toString(){
        return "["+this.start+", "+this.end+"]";
    }
}

class Map{
    String source;
    String dest;
    List<long[]> mappings;
    List<Range> ranges;
    Map(String source, String dest){
        this.source = source;
        this.dest = dest;
        this.mappings = new ArrayList<long[]>();
        this.ranges = new ArrayList<Range>();
    }
    void addEntry(long source, long dest, long range){
        long[] mapping = {source, dest, range};
        mappings.add(mapping);
        ranges.add(new Range(source, source+range));
    }

    long get(long source){
        for (long[] mapping : this.mappings) {
            if(source >= mapping[0] && source <= mapping[0]+mapping[2]){
                return source+(mapping[1]-mapping[0]);
            }
        }
        return source;
    }
}

class Test extends Thread {
    Range range;
    HashMap<String, Map> maps;
    Test(Range range, HashMap<String, Map> maps) {
        this.range = range;
        this.maps = maps;
    }
    public void run()
    {
        try {
            // Displaying the thread that is running
            System.out.println(
                "Thread " + Thread.currentThread().threadId()
                + " is running");
            long lowest = Long.MAX_VALUE;
            for (long i=this.range.start; i<this.range.end; i++){
                String source = "seed";
                long val = i;
                while (!source.equals("location")) {
                    Map map = maps.get(source);
                    val = map.get(val);
                    source = map.dest;
                }
                if (val < lowest) lowest = val;
            }
            System.out.println("Thread " + Thread.currentThread().threadId() + " lowest: "+lowest);
        }
        catch (Exception e) {
            // Throwing an exception
            System.out.println("Exception is caught");
        }
    }
}

public class D05 {
    static List<String> raw;
    static List<Long> seeds;
    static HashMap<String, Map> maps;
    static List<Range> seeds2;
    static void parseInput(){
        //raw = InputFile.readFile("./Tim3/src/input/05.txt");
        raw = InputFile.readFile("./Tim3/src/input/05Sample.txt");
        seeds = new ArrayList<>();
        for (String seed : raw.get(0).split(" ")) {
            if  (Utils.isNumeric(seed)){
                seeds.add(Long.parseLong(seed));
            }
        }
        //System.out.println(seeds);
        maps = new HashMap<>();
        Map currMap = null;
        Pattern mapPattern = Pattern.compile("(?<source>.+)-to-(?<dest>.+) map:");
        Pattern numsPattern = Pattern.compile("(?<dest>\\d+) (?<source>\\d+) (?<range>\\d+)");
        for (int i=0; i<raw.size(); i++) {
            if (i==0) continue;
            String line = raw.get(i);
            Matcher mapMatcher = mapPattern.matcher(line);
            Matcher numsMatcher = numsPattern.matcher(line);
            if (mapMatcher.find()){
                currMap = new Map(mapMatcher.group("source"), mapMatcher.group("dest"));
                maps.put(currMap.source, currMap);
            } else if (numsMatcher.find()){
                currMap.addEntry(
                    Long.parseLong(numsMatcher.group("source")),
                    Long.parseLong(numsMatcher.group("dest")),
                    Long.parseLong(numsMatcher.group("range"))
                );
            }
        }
        seeds2 = new ArrayList<>();
        for (int i=0; i<seeds.size(); i+=2){
            long start = seeds.get(i);
            long len = seeds.get(i+1);
            seeds2.add(new Range(start, start+len));
        }
    }
    static long part1(){
        long[] values = seeds.stream().mapToLong(i->i).toArray();
        String source = "seed";
        while (!source.equals("location")) {
            Map map = maps.get(source);
            for (int i=0; i<values.length; i++){
                long val = values[i];
                long newVal = map.get(val);
                values[i] = newVal;
            }
            source = map.dest;
        }
        long min = Long.MAX_VALUE;
        for (long val: values){
            if (val<min) min = val;
        }

        return min;

    }

    static long part2(){
        long lowest = Long.MAX_VALUE;
        for (Range seed_range : seeds2) {
            System.out.println(seed_range);
            for (long i=seed_range.start; i<seed_range.end; i++){
                if(i%100000000==0){
                    DateTimeFormatter dtf = DateTimeFormatter.ofPattern("dd.MM HH:mm:ss");
                    LocalDateTime now = LocalDateTime.now();
                    System.out.println(dtf.format(now)+" "+i);
                }
                String source = "seed";
                long val = i;
                while (!source.equals("location")) {
                    Map map = maps.get(source);
                    val = map.get(val);
                    source = map.dest;
                }
                if (val < lowest) lowest = val;
            }

        }
        return lowest;
    }
    static void part2_1(){
        for (Range seed_range : seeds2) {
            Test object= new Test(seed_range, maps);
            object.start();
        }
    }
    public static void main(String[] args) {
        parseInput();
        System.out.println("Solution Part1: "+part1());
        //System.out.println("Solution Part2: "+part2());
        part2_1();

    }
}
