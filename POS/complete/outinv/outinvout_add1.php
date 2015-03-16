<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php
	include("mysqlcntdb.php");
	$cntid="outi";	
	include("counter.php");
	$dt=date("Y-m-d");
//-------------- 將客戶資料表中的資料全部取出--------------
	$SQLStr = "SELECT * FROM cust";
	$res = mysql_query($SQLStr);
?>
<script language="JavaScript">
//-------------- 檢查數量--------------
function checkprodqty(fld){
   if (fld.value == ""){
      alert("請輸入產品數量!");
      fld.focus();
      fld.select();
   }
}
</script>
<form name="form1" method="post" action="outinv/outinvout_add2.php" >
  <table width="780" border="1" cellpadding="0" cellspacing="0" align="center" bordercolor="#000000" >
    <tr > <td   bgcolor="#FFFFFF">    
        <table  border="1" align="center" bgcolor="#99CCFF" cellpadding="0" cellspacing="0" width="780">
          <tr  bgcolor="#99CCFF"> 
            <td  bgcolor="#9933FF" align="center"> 
             <font color="#FFFFFF">新增銷貨單資料</font>
            </td> 
			  <td align="center"> 
              <input type="submit" name="submit" value="新增銷貨資料">
            </td>                 
          </tr>
        </table>	
        <table width="780" border="1" cellpadding="0" cellspacing="0" bgcolor="#99CCFF"  align="center">
          <tr> 
            <td width="103" align="center">銷貨單號</td>
            <td width="187"><input type="text" name="outino" size="10" value="<?=$outicnt;?>">                
            </td>
            <td width="96" align="center">銷貨日期</td>
            <td width="351"> 
                <input type="text" name="outidate" size="12" value="<?=date("Y-m-d")?>">
            </td>
          </tr>        
          <tr>            
            <td width="96" height="22" align="center">客戶編號</td>
           <!-- </td>-->
            <td width="187" height="22">
<?
	if ($res)
	{
	  $num = mysql_num_rows($res);

//---------- 將客戶名稱的欄位值呈現於網頁上-------------- 
          echo "<select name='outicustno'>";
	  for ($i=0;$i<$num;$i++)
	  {
	    $row = mysql_fetch_array($res);
	    echo "<option value='" . $row['custno'] . "'>" .$row['custno'] . "/" . $row['custname'] . "</option>";
	  }
            echo "</select>";
//-------------- 將客戶名稱的欄位值以呈現於網頁上--------------

	}		
	else //-------------- 客戶資料表中無客戶資料--------------
		echo "目前無客戶區分";
?>           
            </td>
			 <td width="96" align="center">報價單號</td>
            <td width="351"> 
                <input type="text" name="outiquno" size="10" value="<?=$outiquno;?>">
            </td>
          </tr>        
        </table>       
        <table width="780"  border="1"   bgcolor="#99CCFF" cellpadding="0" cellspacing="0" align="center">
         <tr>
            <td  align="center" width="542">產品編號/產品名稱/單位/單價</td>          
            <td width="238" align="center">銷貨數量</td>  
          </tr>        
 <?php		  
//-------------- 輸入銷售產品資料欄位值--------------
	  for ($i=0;$i<8;$i++)
		 { 
          echo "<tr>";          
            echo "<td align='center'>";
//-------------- 將產品資料表中的資料全部取出--------------	
	$SQLStr = "SELECT product.*, prun.* FROM product AS product ";
	$SQLStr .= "LEFT JOIN prun AS prun ON product.produnit =  prun.prunno ";
	$res = mysql_query($SQLStr);
	if ($res)
	{
	  $num = mysql_num_rows($res); 
          echo "<select name='outiprodno[]'>";
	  for ($j=0;$j<$num;$j++)
	  {
	    $row = mysql_fetch_array($res);	
//-------------- 將產品相關的欄位值呈現於網頁上--------------			
	    echo "<option value='" . $row['prodno'] . "'>" . $row['prodno'] ."&nbsp;&nbsp;&nbsp;/&nbsp;&nbsp;&nbsp;" . $row['prodname'] ."&nbsp;&nbsp;&nbsp;/&nbsp;&nbsp;&nbsp;".$row['prunname']. "&nbsp;&nbsp;&nbsp;/&nbsp;&nbsp;&nbsp;".$row['prodspric']. "</option>";
	  }
            echo "</select>";
//-------------- 輸入銷售數量欄位值以及呈現於網頁上--------------
     echo "</td>";			      
     echo "<td align='center'><input name='outiprodqty[]' type='text' size='6' maxlength='6' onblur='checkprodqty(this)'></td>";

	}		
	else
		echo "目前無產品";			
    }
		  ?>	  
        </table>     
      </td>
    </tr>
  </table>
</form>
</body>
</html>
