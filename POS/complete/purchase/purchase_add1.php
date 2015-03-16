<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php	
	include("mysqlcntdb.php");
	//-------------- 將計數器資料表中的採購計數值取出--------------
	$cntid="purc";
	include("counter.php");
	$dt=date("Y-m-d");

?>
<script language="JavaScript">
//-------------- 檢查產品數量--------------
function checkprodqty(fld){
   if (fld.value == ""){
      alert("請輸入產品數量!");
      fld.focus();
      fld.select();
   }
}
</script>	
<form name="form1" method="post" action="purchase/purchase_add2.php">
  <table width="780" border="1" cellpadding="0" cellspacing="0" align="center" bordercolor="#0000FF">
    <tr>
	  <td   bgcolor="#FFFFFF">  
	<table  border="1" align="center" bgcolor="#99CCFF" cellpadding="0" cellspacing="0" width="780">
          <tr  bgcolor="#99CCFF"> 
            <td  bgcolor="#9933FF" align="center"> 
             <font color="#FFFFFF">新增採購單資料</font>
            </td> 
			  <td align="center"> 
              <input type="submit" name="submit" value="新增採購單資料">
            </td>                 
          </tr>
        </table>	
      <table width="780" border="1" cellpadding="0" cellspacing="0" bgcolor="#99CCFF"  align="center">        
	      <tr> 
            <td width="103" align="center">採購單號</td>
            <td width="187"><input type="text" name="purcmtranno" size="10" value="<?=$purccnt;?>">                
            </td>
            <td width="96" align="center">交貨日期</td>
            <td width="351"> 
                <input type="text" name="purcmdate" size="12" value="<?=date("Y-m-d")?>">
            </td>
          </tr>        
          <tr>            
            <td width="96" height="22" align="center">廠商編號</td>
           <!-- </td>-->
            <td width="187" height="22">
<?php
    //-------------- 將廠商資料表中的資料全部取出--------------
	$SQLStr = "SELECT * FROM vend";
	$res = mysql_query($SQLStr);
	if ($res)
	{
	  $num = mysql_num_rows($res);
    //---------- 將廠商編號/名稱的欄位值呈現於網頁上--------------   
          echo "<select name='purcmvend'>";
	  for ($i=0;$i<$num;$i++)
	  {
	    $row = mysql_fetch_array($res);
	    echo "<option value='" . $row['vendno'] . "'>" .$row['vendno'] ." / ". $row['vendname'] . "</option>";
	  }
            echo "</select>";	
	}		
	else
	// 資料表中無廠商資料 
		echo "目前無廠商資料";
?>           
            </td>
			 <td width="96" align="center">採購類別</td>
            <td width="351"> 
                <input type="text" name="purcmtype" size="10">
            </td>
          </tr>        
        </table>       
		<table width="780"  border="1"   bgcolor="#99CCFF" cellpadding="0" cellspacing="0" align="center">        
          <tr>
            <td  align="center">產品編號/產品名稱/單價</td>
            <td  align="center">採購數量</td>
            <td  align="center"></td>           
          </tr>
  <?php		  
        //-------------- 將產品編號/名稱/單價的欄位值呈現於網頁上--------------		
		  for ($i=0;$i<8;$i++)
		 {         
		    echo "<tr>";
            echo "<td align='center'>";
              //---------- 將產品編號/名稱的欄位值呈現於網頁上--------------	
			  $SQLStr = "SELECT * FROM product";
	          $res = mysql_query($SQLStr);
	          if ($res)
	          {
	            $num = mysql_num_rows($res); 
                echo "<select name='purchprodno[]'>";
	            for ($k=0;$k<$num;$k++)
	            {
	              $row = mysql_fetch_array($res);
	              echo "<option value='" . $row['prodno'] . "'>" . $row['prodno'] ."/". $row['prodname'] . "/".$row['prodipric']."</option>";
				  $purchpric[$k]=$row['prodipric'];
	            }
                  echo "</select>";			
	          }		
	          else 
              //---------- 無產品資料--------------------			  
		          echo "目前無產品資料";				 
			 echo "</td>"; 
            echo "<td align='center'><input name='purchprodqty[]' type='text' size='6' maxlength='6' onblur='checkprodqty(this)'></td>";
           echo "</tr>";
		  }  
		  ?>	  
        </table>     
      </td>
    </tr>
  </table>
</form>
</body>
</html>