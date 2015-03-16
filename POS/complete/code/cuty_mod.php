<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>修改客戶類別</title>
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
// -----取出客戶類別----------- 	
$SQLStr = "SELECT * FROM cuty";	
$res = mysql_query($SQLStr);
// -----取出客戶類別-----------	
?>
<form name="form1" method="post" action="./code/cuty_mod_db.php">
  <table width="750" border="1" cellpadding="0" cellspacing="0" align="center" bordercolor="#0000FF">
    <tr> 
      <td bgcolor="#CCFFFF"> 
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%"  bgcolor="#CCFFFF" align="center"> 
             <font  color="#000000">修改客戶類別</font>
            </td>           
          </tr>
        </table>
  <table width="750" border="1" cellspacing="0" cellpadding="0" bordercolor="#9999FF">
    <tr>
      <td>
        <table width="750" border="1" cellspacing="0" bgcolor="#FFFFFF">
          <tr> 
            <td bgcolor="#CCCCCC" align="center">現有客戶類別代碼</td>
			<td bgcolor="#CCCCCC" align="center">現有客戶類別名稱</td>
          </tr>
          <?
	       //---------- 取出現有客戶類別並呈現於網頁上----------
	       $sql="select * from cuty ";
           $rows=mysql_query($sql);
           while(list($cutyno , $cutyname )=@mysql_fetch_row($rows)) {
           echo "
                 <tr bgcolor='#F7F7F7'>
                 <td><font size='-1'>$cutyno</font></td>
                 <td><font size='-1'>$cutyname</font></td>                
                 </tr>
                 ";
            }
	        //---------- 取出現有客戶類別並呈現於網頁上----------
           ?>    
	   </table>
      </td>
    </tr>
 </table>
 <table width="400" border="0" align="center">          
          <tr > 
            <td   bgcolor="#0000CC" align="center" ><font color="#FFFFFF">類別</font> 
                <input type="text" name="cutyno">
				<input type="text" name="cutyname">
                <input type="submit" name="Submit" value="修改">
            </td>
			
          </tr> 
	 </table>        
</table>
</form>

