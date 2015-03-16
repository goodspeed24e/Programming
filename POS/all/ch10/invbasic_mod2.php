<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php   
    include("mysqlcntdb.php");
// -------------取出選擇之產品的資料---------------	
	$SQLStr = "SELECT *  FROM product  WHERE prodno='$prodno'";	
	$res = mysql_query($SQLStr);	
// -------------取出產品類別的資料---------------		
	$SQLStr2 = "SELECT * FROM prty";
	$res2 = mysql_query($SQLStr2);	

	if (mysql_num_rows($res)>0) 
	{
	$row = mysql_fetch_array($res);
?>
<!----執行修改頁面呈現,傳入搜尋條件給invbasic_mod3.php------------------------->
<form name="form1" method="post" action="invbasic_mod3.php">
<table width="780" border="1" cellpadding="0" cellspacing="0" align="center" bordercolor="#0000FF">
    <tr> 
	<table  border="1" align="center" bgcolor="#99CCFF" cellpadding="0" cellspacing="0" width="780">
          <tr  bgcolor="#99CCFF"> 
            <td  bgcolor="#9933FF" align="center"> 
             <font color="#FFFFFF">修改產品基本資料</font>
            </td> 
			  <td align="center"> 
              <input type="submit" name="submit" value="修改產品資料">
            </td>                 
          </tr>
        </table>
<!----資料呈現,顯示產品搜尋結果顯示----------->				
        <table width="780" border="1" cellpadding="0" cellspacing="0" bgcolor="#99CCFF"   bordercolor="#FFFFFF" align="center">
          <tr> 
            <td width="103" align="center">產品編號</td>
            <td width="187"><?=$row['prodno']?> 
                <input  type="hidden" name="prodno" size="10" value="<?=$row['prodno']?>">
            </td>
            <td width="96" align="center">產品名稱</td>
            <td width="351">		
                <input type="text" name="prodname" size="40" value="<?=$row['prodname']?>">
            </td>
          </tr>
          <tr> 
            <td width="103" align="center">規格說明</td>
            <td width="187">
                 <input type="text" name="prodsdesp" size="40" value="<?=$row['prodsdesp']?>">
            </td>
            <td width="96" align="center">產品類別</td>
            <td width="351">
<?php
//--------------------- 將類別名稱的欄位值,呈現於網頁上,供選擇---------- 
	if ($res2)
	{
	  $num2 = mysql_num_rows($res2);	
          echo "<select name='prodtype'>";
	  for ($i=0;$i<$num2;$i++)
	  {
	    $row2 = mysql_fetch_array($res2);
	    echo "<option value='" . $row2['prtyno'] . "'>" . $row2['prtyname'] . "</option>";
	  }
            echo "</select>";	
	}		
	else 
		echo "目前無類別區分";
?>	              
            </td>
          </tr>
          <tr> 
            <td width="103" align="center">供應廠商</td>
            <td width="187">
<?php
//------------------------- 將廠商資料表中的資料全部取出------------------------
	$SQLStr3 = "SELECT * FROM vend";
	$res3 = mysql_query($SQLStr3);
	if ($re3s)
	{
	  $num3 = mysql_num_rows($res3);

//------------------------- 將廠商名稱的欄位值,呈現於網頁上,供選擇 ----------------------------
          echo "<select name='prodvend'>";
	  for ($i=0;$i<$num3;$i++)
	  {
	    $row3 = mysql_fetch_array($res3);
	    echo "<option value='" . $row3['vendno'] . "'>" . $row3['vendname'] . "</option>";
	  }
            echo "</select>";	
	}		
	else
		echo "目前無廠商資料";
?>
            </td>
            <td width="96" align="center">單位</td>
            <td width="351">
<?php
//------------------------- 將產品單位資料表中的資料全部取出------------------------	
	$SQLStr4 = "SELECT * FROM prun";
	$res4 = mysql_query($SQLStr4);
	
	if ($res4)
	{
	  $num4 = mysql_num_rows($res4);
//------------------------- 將產品單位名稱的欄位值,呈現於網頁上,供選擇 ----------------------------
          echo "<select name='produnit'>";
	  for ($i=0;$i<$num4;$i++)
	  {
	    $row4 = mysql_fetch_array($res4);
	    echo "<option value='" . $row4['prunno'] . "'>" . $row4['prunname'] . "</option>";
	  }
            echo "</select>";
	}		
	else 
		echo "目前產品單位無區分";
?>	       
            </td>
          </tr>
		   <tr> 
            <td width="103" align="center">成本價格</td>
            <td width="187"><?=$prodipric ?> 
                <input type="text" name="prodipric" size="10" value="<?=$row['prodipric']?>">
            </td>
            <td width="96" align="center">售價</td>
            <td width="351">
                <input type="text" name="prodspric" size="10" value="<?=$row['prodspric']?>">
            </td>
          </tr>
          <tr> 
            <td width="103" height="22" align="center">安全存量</td>
            <td width="187" height="22">
              <input type="text" name="prodsave" size="10" value="<?=$row['prodsave']?>">
            </td>
            <td width="96" height="22" align="center">最近進貨日</td>              
            <td width="187" height="22">			   
              <input type="text" name="prodidate" value="<?=$row['prodidate']?>">
            </td>
          </tr>         
         <tr>
			<td width="103" height="22" align="center">最近出貨日</td>
            <td width="187" height="22">
			<input type="text" name="prododate" value="<?=$row['prododate']?>">                
            </td>           
          </tr>		     
        </table>
        <br>        
      </td>
    </tr>
  </table>
</form>
<?
}
else
	{
	 $msg="無此產品";
	 include("windowsclose.php");		
	} 
?>
</body>
</html>

