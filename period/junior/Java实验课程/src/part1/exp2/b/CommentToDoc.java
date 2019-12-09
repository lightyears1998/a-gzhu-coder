/**
    <h1>Javadoc工具演示</h1>

    <ul>
        <li>可以在Javadoc中使用html标签。</li>
        <li>使用<code>javadoc CommentToDoc.java</code>命令来生成CommentToDoc.java的JavaDoc。</li>
        <li>只有以“/**”开头的注释才会被加入JavaDoc。</li>
        <li>如果在简体中文环境中使用UTF8编码的源代码提示“无法映射的GBK字符”，
        则可以使用<code>-encoding utf8</code>参数来指定源程序的编码。</li>
    </ul>
 */
public class CommentToDoc {
    /** 
        主方法，作为Java应用程序的入口
        @param args 传递的命令行参数
    */
    public static void main(String[] args) {
        /** 即使使用Javadoc格式注释，在函数实现中的注释也不会被加入到JavaDoc中 */
        System.out.println("我在学习Java语言");  // 输出“我在学习Java语言”
    }
}
