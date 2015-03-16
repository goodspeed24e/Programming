<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php	
	include("mysqlcntdb.php");
	$cntid="tran";	
	include("counter.php");
	$dt=date("Y-m-d");
//-------------- 將廠商資料表中的資料全部取出--------------
	$SQLStr = "SELECT * FROM vend";
	$res = mysql_query($SQLStr);

?>
<!---------------- 資料欄位檢查-------------->
<script language="JavaScript">
//-------------- 檢查數量--------------
function checkprodqty(objEle){
   if (objEle.value == ""){
      alert("請輸入產品數量!");
      objEle.focus();
      objEle.select();
   }
}
</script>	
<!------進入ininvpur_add3.php ,將進貨資料輸入資料庫中---------->
<form name="form1" method="post" action="ininv/ininvpur_add3.php">
  <table width="780" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
	<table  border="1" align="center" bgcolor="#99CCFF" cellpadding="0" cellspacing="0" width="780">
          <tr  bgcolor="#99CCFF"> 
            <td  bgcolor="#9933FF" align="center"> 
             <font color="#FFFFFF">依採購單輸入進貨資料</font>
            </td> 
			  <td align="center"> 
              <input type="submit" name="submit" value="新增進貨資料">
            </td>                 
          </tr>
        </table>	
      <table width="780" border="1" cellpadding="0" cellspacing="0" bgcolor="#99CCFF"  align="center">        
	      <tr> 
            <td width="103" align="center">進貨單號</td>
            <td width="187"><input type="text" name="tranno" size="10" value="<?=$trancnt;?>">                
            </td>
            <td width="96" align="center">進貨日期</td>
            <td width="351"> 
                <input type="text" name="trandate" size="12" value="<?=date("Y-m-d")?>">
            </td>
          </tr>
        
          <tr>            
            <td width="96" height="22" align="center">廠商編號</td>
           <!-- </td>-->           
            <td width="187">
<?php
//-------------------- 將廠商資料表中的資料全部取出----------------------------
	$SQLStr = "SELECT * FROM vend";
	$res = mysql_query($SQLStr);
	if ($res)
	{
	  $num = mysql_num_rows($res);
//------------------- 呈現廠商名稱的欄位值,供選擇------------------------------------
           echo "<select name='tranvendno'>";
	  for ($i=0;$i<$num;$i++)
	  {
	    $row = mysql_fetch_array($res);
	    echo "<option value='" . $row['vendno'] . "'>" . $row['vendname'] . "</option>";
	  }
            echo "</select>";	
	}		
	else 
		echo "目前廠商無名稱";
?>
            </td>
			<td width="96" align="center">採購單號</td>
            <td width="351"><?=$tranpono;?> 
                <input type="hidden" name="tranpono" size="12" value="<?=$tranpono;?>">
            </td>
          </tr>        
        </table>       
		<table width="780"  border="1"   bgcolor="#99CCFF" cellpadding="0" cellspacing="0" align="center">        
          <tr>
            <td  align="center" width="542">產品編號/產品名稱/採購數量/單價</td>          
            <td width="238" align="center">進貨數量</td>  
          </tr>
  <?php		  
    //-------------- 輸入進貨產品資料欄位值--------------
	  for ($i=0;$i<8;$i++)
		 { 
          echo "<tr>";          
            echo "<td align='center'>";
    //-------------- 將採購資料表中符合條件的資料全部取出--------------	
    $SQLStr = "SELECT product.*, purchase.* FROM purchase AS purchase ";
	$SQLStr .= "LEFT JOIN product AS product ON purchase.purchprodno =  product.prodno WHERE purchtranno='$tranpono'";	
	$res = mysql_query($SQLStr);
	if ($res)
	{
	  $num = mysql_num_rows($res); 
          echo "<select name='tranprodno[]'>";
	  for ($j=0;$j<$num;$j++)
	  {
	    $row = mysql_fetch_array($res);		
	    echo "<option value='" . $row['purchprodno'] . "'>" . $row['purchprodno'] ."&nbsp;&nbsp;&nbsp;/&nbsp;&nbsp;&nbsp;" . $row['prodname'] ."&nbsp;&nbsp;&nbsp;/&nbsp;&nbsp;&nbsp;".$row['purchprodqty']. "&nbsp;&nbsp;&nbsp;/&nbsp;&nbsp;&nbsp;".$row['purchpric']. "</option>";
	  }
            echo "</select>";
    //-------------- 將採購及產品的欄位值呈現於網頁上--------------
     echo "</td>";			      
     echo "<td align='center'><input name='tranprodqty[]' type='text' size='6' maxlength='6' onblur='checkprodqty(this)'></td>";

	}
	//-------------- 採購資料表中無符合資料--------------
	else 
 	 echo "目前無採購資料";
	 echo "</td>";			      
     echo "<td align='center'>&nbsp;</td>";
    }	
		  ?>	  
        </table>     
      </td>
    </tr>
  </table>
</form>
</body>
</html>
