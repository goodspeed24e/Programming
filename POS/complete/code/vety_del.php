<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>刪除廠商類別</title>
<style type="text/css">
<!--
.style1 {color: #FF0000}
-->
</style>
</head>
<?php
//----------連接資料庫----------
	include("mysqlcntdb.php");
//----------連接資料庫----------
if ($check == del) 
	{
		//---------- 從資料庫中廠商類別刪除----------
		$SQLStr = "DELETE FROM vety WHERE vetyno = '$vetyno' LIMIT 1 ";
		mysql_query("SET NAMES 'big5'");
        mysql_query("SET CHARACTER SET big5"); 
		mysql_query($SQLStr);
		//---------- 從資料庫中廠商類別刪除---------- 
	}

	// ----------取出所有廠商類別 ----------
	$SQLStr = "SELECT * FROM vety";	
	$res = mysql_query($SQLStr);
	// ----------取出所有廠商類別----------	
?>
<form name="form1" method="post" action="./code/vety_del_db.php">
  <table width="750" border="1" cellpadding="0" cellspacing="0" align="center" bordercolor="#0000FF">
    <tr> 
      <td  bgcolor="#CCFFFF"> 
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%" bgcolor="#CCFFFF" align="center"> 
             <font bgcolor="#CCFFFF">刪除廠商類別</font>
            </td>            
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
	       //---------- 取出現有廠商類別並呈現於網頁上---------- 
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
		  //---------- 取出現有廠商類別名稱並呈現於網頁上---------- 
          ?>    
	   </table>
      </td>
    </tr>
 </table>
 <table width="400" border="0" align="center">          
          <tr > 
            <td bgcolor="#0000CC" align="center" ><font color="#FFFFFF">類別</font>  
                <input type="text" name="vetyno">
				<input type="text" name="vetyname">
                <input type="submit" name="Submit" value="刪除">
            </td>			
          </tr> 
	 </table>        
</table>
</form>

