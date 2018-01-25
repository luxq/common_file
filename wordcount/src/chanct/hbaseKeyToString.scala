package chanct
import scala.collection.JavaConversions._
import scala.util.parsing.json.JSONObject
import org.apache.spark.api.python.Converter
import org.apache.hadoop.hbase.client.Result
import org.apache.hadoop.hbase.io.ImmutableBytesWritable
import org.apache.hadoop.hbase.util.Bytes
import org.apache.hadoop.hbase.KeyValue.Type
import org.apache.hadoop.hbase.CellUtil
/**                                                                                                             
 * Implementation of [[org.apache.spark.api.python.Converter]] that converts an
 * ImmutableBytesWritable to a String
 */
class hbaseKeyToString extends Converter[Any, String] {
  override def convert(obj: Any): String = {
        val key = obj.asInstanceOf[ImmutableBytesWritable]
        Bytes.toStringBinary(key.get())
    }
}