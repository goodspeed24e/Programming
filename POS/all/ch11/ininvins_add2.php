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
<!------進入ininvins_add3 ,將進貨資料輸入資料庫中---------->
<form name="form1" method="post" action="ininv/ininvins_add3.php">
  <table width="780" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
	<table  border="1" align="center" bgcolor="#99CCFF" cellpadding="0" cellspacing="0" width="780">
          <tr  bgcolor="#99CCFF"> 
            <td  bgcolor="#9933FF" align="center"> 
             <font color="#FFFFFF">新增進貨單資料</font>
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
            <td width="187" height="22"><?=$vendno;?><?=$vendname;?>
              <input  type="hidden" name="tranvendno" size="10" value="<?=$vendno;?>">
            </td>
			<td width="96" align="center">採購單號</td>
            <td width="351"> 
                <input type="text" name="tranpono" size="12" value="<?=$tranpono;?>">
            </td>
          </tr>        
        </table>       
		<table width="780"  border="1"   bgcolor="#99CCFF" cellpadding="0" cellspacing="0" align="center">        
          <tr>
            <td  align="center" width="542">產品編號/產品名稱/單位/單價</td>          
            <td width="238" align="center">進貨數量</td>  
          </tr>
  <?php		  
//-------------- 以下拉式呈現同一廠商產品,供選擇進貨產品資料欄位值--------------
	  for ($i=0;$i<8;$i++)
		 { 
          echo "<tr>";          
            echo "<td align='center'>";
//-------------- 將產品資料表中符合條件的資料全部取出,同時以JOIN方式讓產品單位能顯示名稱--------------	
	$SQLStr = "SELECT product.*, prun.* FROM product AS product ";
	$SQLStr .= "LEFT JOIN prun AS prun ON product.produnit =  prun.prunno WHERE prodvend='$vendno'";
	$res = mysql_query($SQLStr);
	if ($res)
	{
	  $num = mysql_num_rows($res); 
          echo "<select name='tranprodno[]'>";
	  for ($j=0;$j<$num;$j++)
	  {
	    $row = mysql_fetch_array($res);		
	    echo "<option value='" . $row['prodno'] . "'>" . $row['prodno'] ."&nbsp;&nbsp;&nbsp;/&nbsp;&nbsp;&nbsp;" . $row['prodname'] ."&nbsp;&nbsp;&nbsp;/&nbsp;&nbsp;&nbsp;".$row['prunname']. "&nbsp;&nbsp;&nbsp;/&nbsp;&nbsp;&nbsp;".$row['prodipric']. "</option>";
	  }
            echo "</select>";
    echo "</td>";			      
     echo "<td align='center'><input name='tranprodqty[]' type='text' size='6' maxlength='6' onblur='checkprodqty(this)'></td>";

	}		
	else
		echo "目前未提供產品資料";			
    }
 ?>	  
        </table>     
      </td>
    </tr>
  </table>
</form>
</body>
</html>
