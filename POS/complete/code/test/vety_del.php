<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>進銷存web based系統</title>
<style type="text/css">
<!--
.style1 {color: #FF0000}
-->
</style>
</head>
<?php
	include("swmcntdb.php");
// 瀏覽次數-- 頭--  counterhead.php + counterbody.php 即成瀏覽次數小程式 
// include("swmcnthead.php");   
		
//簡易留言版-- 頭-- boardead.php + boardbody.php 即成簡易留言版
//    include("swmbdhead.php");
?>
<?php
if ($check == del) 
	{
		// 將類別新增至資料庫中 BEGIN
		$SQLStr = "DELETE FROM vety WHERE vetyno = '$vetyno' LIMIT 1 ";
		mysql_query("SET NAMES 'big5'");
        mysql_query("SET CHARACTER SET big5"); 
		mysql_query($SQLStr);
		// 將類別新增至資料庫中 END
	}

	// 取出所有類別 BEGIN	
	$SQLStr = "SELECT * FROM vety";	
	$res = mysql_query($SQLStr);
	// 取出所有類別 END		
	
?>

<form name="form1" method="post" action="iwmfile_vety_del_db.php">
  <table width="750" border="1" cellpadding="0" cellspacing="0" align="center" bordercolor="#0000FF">
    <tr> 
      <td bgcolor="#FFFFCC"> 
        <table width="400" border="0" align="center">
          <tr> 
            <td width="60%" bgcolor="#9933FF" align="center"> 
             <font color="#FFFFFF">刪除廠商類別</font>
            </td>
            <td width="25%" bgcolor="#9966FF">&nbsp;</td>
            <td width="10%" bgcolor="#9999FF">&nbsp;</td>
            <td width="3%" bgcolor="#9999FF">&nbsp;</td>
            <td width="2%" bgcolor="#99CCFF">&nbsp;</td>
          </tr>
        </table>
  <table width="750" border="1" cellspacing="0" cellpadding="0" bordercolor="#9999FF">
    <tr>
      <td>
        <table width="750" border="1" cellspacing="0" bgcolor="#FFFFFF">
          <tr> 
            <td bgcolor="#CCCCCC" align="center">現有廠商類別代碼</td>
			<td bgcolor="#CCCCCC" align="center">現有廠商類別名稱</td>
          </tr>
<?
	// 取出所有客戶類別名稱並呈現於網頁上 BEGIN
	//$num =@mysql_num_rows($res);
	//for ($i=0;$i<$num;$i++)
	//{
	//$row = mysql_fetch_array($res);
	//echo "<tr><td align='center'>" . $row['cutyname'] . "</td></tr>";
	//}
	// 取出所有客戶類別名稱並呈現於網頁上 END
	$sql="select * from vety ";
    $rows=mysql_query($sql);
    while(list($vetyno , $vetyname )=@mysql_fetch_row($rows)) {
        echo "
             <tr bgcolor='#F7F7F7'>
                <td><font size='-1'>$vetyno</font></td>
                <td><font size='-1'>$vetyname</font></td>                
              </tr>
            ";
    }
?>    
	   </table>
      </td>
    </tr>
 </table>
 <table width="400" border="0" align="center">          
          <tr > 
            <td bgcolor="#99CCFF" align="center" >類別 
                <input type="text" name="vetyno">
				<input type="text" name="vetyname">
                <input type="submit" name="Submit" value="刪除">
            </td>
			
          </tr> 
	 </table>        
</table>
</form>

