<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>銷售類別列表</title>
<style type="text/css">
<!--
.style1 {color: #FF0000}
-->
</style>
</head>
<!!-----------列印設定----------!>
<body>
<!!----------列印設定-----------!>
<?php
//----------連接資料庫----------
	include("mysqlcntdb.php");
//----------連接資料庫----------

//---------- 取出所有銷售類別----------	
$SQLStr = "SELECT * FROM saty";	
$res = mysql_query($SQLStr);
//---------- 取出所有銷售類別----------		
	
?>

<form name="form1" method="post" action="./code/saty_prt_db.php">
  <table width="750" border="1" cellpadding="0" cellspacing="0" align="center" bordercolor="#0000FF">
    <tr> 
      <td bgcolor="#CCFFFF"> 
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%"  bgcolor="#CCFFFF" align="center"> 
             <font  color="#000000">列印銷售類別</font>
            </td>           
          </tr>
        </table>
  <table width="750" border="1" cellspacing="0" cellpadding="0" bordercolor="#9999FF">
    <tr>
      <td>
        <table width="750" border="1" cellspacing="0" bgcolor="#FFFFFF">
          <tr> 
            <td bgcolor="#CCCCCC" align="center">現有銷售類別代碼</td>
			<td bgcolor="#CCCCCC" align="center">現有銷售類別名稱</td>
          </tr>
          <?
	       //---------- 取出所有銷售類別名稱並呈現於網頁上---------- 
	       $sql="select * from saty ";
           $rows=mysql_query($sql);
           while(list($satyno , $satyname )=@mysql_fetch_row($rows)) {
           echo "
                 <tr bgcolor='#F7F7F7'>
                 <td><font size='-1'>$satyno</font></td>
                 <td><font size='-1'>$satyname</font></td>                
                </tr>
               ";
           }
	       //---------- 取出所有銷售類別名稱並呈現於網頁上---------- 
         ?>    
	   </table>
      </td>
    </tr>
 </table>
 <table width="400" border="0" align="center">          
          <tr > 
            <td bgcolor="#0000CC" align="center" > 			                
                <input type="submit" name="Submit" value="列印">
            </td>
			
          </tr> 
	 </table>        
</table>

</form>
</body>

