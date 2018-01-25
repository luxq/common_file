package test
import org.apache.spark.SparkConf
import org.apache.spark.SparkContext

object wordcount {
  def main(args: Array[String]) {
    if(args.length < 1)
    {
      println("usage: <file>")
      return
    }
    val conf = new SparkConf()
    val sc = new SparkContext(conf)
    val line = sc.textFile(args(0))
    line.flatMap(_.split(" ")).map((_,1)).reduceByKey(_+_).collect().foreach(println)
  }
}