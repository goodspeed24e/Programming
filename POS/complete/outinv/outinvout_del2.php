<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>無標題文件</title>
</head>
<body>
<?
    include("mysqlcntdb.php");
	//----------將 product 及 outinv 結合,取出符合條件的所有進貨的資料---------
	$SQLStr = "SELECT outinv.*, product.* FROM outinv AS outinv ";
	$SQLStr .= "LEFT JOIN  product AS  product ON outinv.outiprodno = product.prodno WHERE (outino='$outino' and outiprodno='$outiprodno')";
	$res = mysql_query($SQLStr);		
	//---------- 判斷查詢結果是否有值--------------------------
	if (mysql_num_rows($res)>0)	
	{
	$row = mysql_fetch_array($res);
?>
<!------ 傳給 outinvout_del3.php 檔案  ------>
<form name="form1" method="post" action="outinvout_del3.php">
  <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td  bgcolor="#FFFFFF"> 
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%" bgcolor="#9933FF" align="center"><font color="#FFFFFF">銷貨詳細資訊</font>
            </td>                
          </tr>
	</table>
	<table width="770">
	  <tr>
            <td align="center"> 
              <input type="submit" name="submit" value="刪除銷貨資料">
            </td>
	  </tr>
  </table>
  <!--呈現銷貨資料,供判斷----------> 
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
          <tr>           
            <td width="241" align="center"><font >銷貨單號</font></td>
            <td width="522" align="left"><?=$row['outino']?> 
		      <input  type="hidden" name="outino" size="10" value="<?=$row['outino']?>">
            </td>            
          </tr>
          <tr> 
            <td width="241" align="center"><font >產品編號</font></td>
            <td width="522" align="left"><?=$row['outiprodno']?>
			    <input type="hidden" name="outiprodno" size="10" value="<?=$row['outiprodno']?>">
            </td>
          </tr>
		  <tr> 
            <td width="241" align="center"><font >產品名稱</font></td>
            <td width="522" align="left"><?=$row['prodname']?>			   		   
            </td>
          </tr>         
          <tr>
            <td width="241" height="22" align="center"><font >銷貨日期</font> </td>
            <td width="522" height="22" align="left"><?=$row['outidate']?>               
            </td>            
          </tr>
          <tr>            
            <td width="241" height="22" align="center">客戶編號</td>
            <td width="522" height="22" align="left"><?=$row['outicustno']?>
			<input type="hidden" name="outicustno" size="10" value="<?=$row['outicustno']?>"> 			
            </td>			           
          </tr>
		  <tr>            
            <td width="241" height="22" align="center">報價單號</td>
            <td width="522" height="22" align="left"><?=$row['outipono']?>
			<input type="hidden" name="outicustno" size="10" value="<?=$row['outipono']?>">
			</td>			           
          </tr>
		  <tr>
			<td width="241" height="22" align="center">產品數量</td>
            <td width="522" height="22"><?=$row['outiprodqty']?>
			<input type="hidden" name="outiprodqty" size="6" value="<?=$row['outiprodqty']?>">                 
            </td>           
          </tr>
		  <tr>
			<td width="241" height="22" align="center">產品單位</td>
            <td width="522" height="22"><?=$row['outiunit']?>           
            </td>           
          </tr>
		  <tr> 
            <td width="241" align="center">單價</td>
            <td width="522"><?=$row['outipric']?>
			<input type="hidden" name="outipric" size="6" value="<?=$row['outipric']?>">                   
            </td>
		  </tr>		   
		</td>
    </tr> 
  </table>
</form>
<?
}
else
	{
	 $msg="無此銷貨單";
	 include("windowsclose.php");		
	}
?>
</body>
</html>