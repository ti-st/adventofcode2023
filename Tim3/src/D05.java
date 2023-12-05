import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.HashMap;

import input.InputFile;

class Map{
    String source;
    String dest;
    List<long[]> mappings;
    Map(String source, String dest){
        this.source = source;
        this.dest = dest;
        this.mappings = new ArrayList<long[]>();
    }
    void addEntry(long source, long dest, long range){
        long[] mapping = {source, dest, range};
        mappings.add(mapping);
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

public class D05 {
    public static void main(String[] args) {
        List<String> raw = InputFile.readFile("./Tim3/src/input/05.txt");
        //List<String> raw = InputFile.readFile("./Tim3/src/input/05Sample.txt");
        List<Long> seeds = new ArrayList<>();
        for (String seed : raw.get(0).split(" ")) {
            if  (Utils.isNumeric(seed)){
                seeds.add(Long.parseLong(seed));
            }
        }
        //System.out.println(seeds);
        HashMap<String, Map> maps = new HashMap<>();
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
        long[] values = seeds.stream().mapToLong(i->i).toArray();
        //System.out.println(maps);
        String source = "seed";
        while (!source.equals("location")) {
            Map map = maps.get(source);
            //System.out.println(values[0]);
            for (int i=0; i<values.length; i++){
                long val = values[i];
                long newVal = map.get(val);
                values[i] = newVal;
            }
            source = map.dest;
        }
        //System.out.println();
        //for(int i: values) System.out.println(i);
        long min = Long.MAX_VALUE;
        for (long val: values){
            if (val<min) min = val;
        }

        System.out.println("Solution Part1: "+min);
    }
}
