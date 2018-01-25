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
 * Implementation of [[org.apache.spark.api.python.Converter]] that converts all-                               
 * the records in an HBase Result to a String. In the String, it contains row, column,                          
 * qualifier, timesstamp, type and value                                                                        
 */ 
class hbaseResultToJsonString extends Converter[Any, String]{
    override def convert(obj: Any): String = {
        import collection.JavaConverters._
        val result = obj.asInstanceOf[Result]
        val output = result.listCells.asScala.map(cell =>
            Map(
                    "row" -> Bytes.toStringBinary(CellUtil.cloneFamily(cell)),
                    "cf" -> Bytes.toStringBinary(CellUtil.cloneFamily(cell)),
                    "qualifier" -> Bytes.toStringBinary(CellUtil.cloneQualifier(cell)),
                    "timestamp" -> cell.getTimestamp.toString,
                    "type" -> Type.codeToType(cell.getTypeByte).toString,
                    "value" -> Bytes.toStringBinary(CellUtil.cloneValue(cell))
            )
        )
        //output is an instance of Map which will be translated to json String
        //Hbase will escape "\n", so it is safe to use "\n" to join json.
        output.map(JSONObject(_).toString()).mkString("\n")
    }
}
