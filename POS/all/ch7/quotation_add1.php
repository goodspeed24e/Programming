<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php	
	include("mysqlcntdb.php");
    //-------------- 將計數器資料表中的報價計數值取出--------------	
	$cntid="quot";
	include("counter.php");	

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

<form name="form1" method="post" action="quotation/quotation_add2.php">
  <table width="780" border="1" cellpadding="0" cellspacing="0" align="center" bordercolor="#0000FF">
    <tr> 
	 <td   bgcolor="#FFFFFF"> 
	<table  border="1" align="center" bgcolor="#99CCFF" cellpadding="0" cellspacing="0" width="780">
          <tr  bgcolor="#99CCFF"> 
            <td  bgcolor="#9933FF" align="center"> 
             <font color="#FFFFFF">新增報價單資料</font>
            </td> 
			  <td align="center"> 
              <input type="submit" name="submit" value="新增報價單資料">
            </td>                 
          </tr>
        </table>	
      <table width="780" border="1" cellpadding="0" cellspacing="0" bgcolor="#99CCFF"  align="center">        
	      <tr> 
            <td width="203" align="center">報價單號</td>
            <td width="187"><input type="text" name="quwkno" size="10" value="<?=$quotcnt;?>">                
            </td>
            <td width="96" align="center">銷售類別</td>
            <td width="251"> 
<?php
    // -------------取出所有銷售類別的資料---------------
    $SQLStr3 = "SELECT * FROM saty";
	$res3 = mysql_query($SQLStr3);
	if ($res3)
	{
	  $num3 = mysql_num_rows($res3);
    //---------- 將銷售類別編號/名稱的欄位值呈現於網頁上--------------   
          echo "<select name='quwktype'>";
	  for ($i=0;$i<$num3;$i++)
	  {
	    $row3 = mysql_fetch_array($res3);
	    echo "<option value='" . $row3['satyno'] . "'>" .$row3['satyno'] . $row3['satyname'] . "</option>";
	  }
            echo "</select>";		
	}		
	else 
    //--------------- 銷售類別資料表中無類別資料---------------
		echo "目前銷售無類別";
?>         
            </td>
          </tr>
        
          <tr>           
            <td width="196" height="22" align="center">客戶編號/名稱</td>
           <!-- </td>-->
            <td width="187" height="22">
<?php
    // -------------取出所有客戶的資料---------------
    $SQLStr = "SELECT * FROM cust";
	$res = mysql_query($SQLStr);
	if ($res)
	{
	  $num = mysql_num_rows($res);
    //---------- 將客戶編號/名稱的欄位值呈現於網頁上,供選擇--------------   
          echo "<select name='quwkcust'>";
	  for ($i=0;$i<$num;$i++)
	  {
	    $row = mysql_fetch_array($res);
	    echo "<option value='" . $row['custno'] . "'>" .$row['custno'] ." / ". $row['custname'] . "</option>";
	  }
            echo "</select>";		
	}		
	else 
		echo "目前客戶無區分類別";
?>           
            </td>
			 <td width="96" align="center"></td>
            <td width="251">            
            </td>
          </tr>        
        </table>       
		<table width="780"  border="1"   bgcolor="#99CCFF" cellpadding="0" cellspacing="0" align="center">        
          <tr>
            <td  align="center">產品編號/產品名稱/售價</td>
            <td  align="center">報價數量</td>                      
          </tr>
  <?php		  
         //-------------- 將銷售產品編號/名稱的欄位值呈現於網頁上,供選擇及輸入報價數量--------------
		
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
                echo "<select name='quwkprod[]'>";
	            for ($k=0;$k<$num;$k++)
	            {
	              $row = mysql_fetch_array($res);
	              echo "<option value='" . $row['prodno'] . "'>" . $row['prodno'] ."/". $row['prodname'] . "/".$row['prodspric']."</option>";
				  $quwkpric[$k]=$row['prodspric'];
	            }
                  echo "</select>";			
	          }		
	          else 
             //---------- 無產品資料--------------------			  
		          echo "目前無產品資料";				 
			 echo "</td>";  
             //---------- 輸入報價及產品的欄位值於網頁上--------------		
             echo "<td align='center'><input name='quwkqty[]' type='text' size='6' maxlength='6' onblur='checkprodqty(this)'></td>";	
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