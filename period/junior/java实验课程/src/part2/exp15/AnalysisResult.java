import java.io.*;
import java.util.*;

// 常用方法签名：
// FileWriter(file: File, append: boolean)

public class AnalysisResult {
    public static void main(String[] args) {
        File fileInput = new File("score.txt");
        File fileOutput = new File("scoreAnalysis.txt");
        try {
            Reader reader = new FileReader(fileInput);  // Windows平台上文件编码须为gbk
            BufferedReader bufferedReader = new BufferedReader(reader);
            Writer writer = new FileWriter(fileOutput, true);
            BufferedWriter bufferedWriter = new BufferedWriter(writer);
            
            String line = null;
            while ((line = bufferedReader.readLine()) != null) {
                Analyzer analyzer = new Analyzer(line);
                double totalScore = analyzer.getTotalScore();
                double averageScore = analyzer.getAverageScore();
                
                String name = line.split(": ")[1].split(",")[0];
                System.out.printf("%s 总分：%f 平均分：%f\n", name, totalScore, averageScore);
            } 

            bufferedReader.close();
            bufferedWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        } 
    }
}


class Analyzer {
    Scanner scanner;
    double totalScore, averageScore;

    Analyzer(String line) {

        Scanner scanner = new Scanner(line);
        scanner.useDelimiter("[^\\d.]+");  // 不能是可能产生空字闭包的[^\\d.]*

        int count = 0;
        while (scanner.hasNextDouble()) {
            double score = scanner.nextDouble();

            System.out.println(score);

            totalScore += score;
            ++count;
        }
        averageScore = totalScore / count;

        scanner.close();
    }

    double getTotalScore() {
        return totalScore;
    }

    double getAverageScore() {
        return averageScore;
    }
}
