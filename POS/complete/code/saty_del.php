<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>�R���P�����O</title>
<style type="text/css">
<!--
.style1 {color: #FF0000}
-->
</style>
</head>
<?php
//----------�s����Ʈw----------
	include("mysqlcntdb.php");
//----------�s����Ʈw----------
if ($check == del) 
	{
		//---------- �q��Ʈw���P�����O�R��----------
		$SQLStr = "DELETE FROM saty WHERE satyno = '$satyno' LIMIT 1 ";
		mysql_query("SET NAMES 'big5'");
        mysql_query("SET CHARACTER SET big5"); 
		mysql_query($SQLStr);
		//---------- �q��Ʈw���P�����O�R��---------- 
	}

	// ----------���X�Ҧ��P�����O ----------
	$SQLStr = "SELECT * FROM saty";	
	$res = mysql_query($SQLStr);
	// ----------���X�Ҧ��P�����O----------	
?>
<form name="form1" method="post" action="./code/saty_del_db.php">
  <table width="750" border="1" cellpadding="0" cellspacing="0" align="center" bordercolor="#0000FF">
    <tr> 
      <td  bgcolor="#CCFFFF"> 
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%" bgcolor="#CCFFFF" align="center"> 
             <font bgcolor="#CCFFFF">�R���P�����O</font>
            </td>            
          </tr>
        </table>
  <table width="750" border="1" cellspacing="0" cellpadding="0" bordercolor="#9999FF">
    <tr>
      <td>
        <table width="750" border="1" cellspacing="0" bgcolor="#FFFFFF">
          <tr> 
            <td bgcolor="#CCCCCC" align="center">�{���P�����O�N�X</td>
			<td bgcolor="#CCCCCC" align="center">�{���P�����O�W��</td>
          </tr>
          <?
	       //---------- ���X�{���P�����O�çe�{������W---------- 
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
		  //---------- ���X�{���P�����O�W�٨çe�{������W---------- 
          ?>    
	   </table>
      </td>
    </tr>
 </table>
 <table width="400" border="0" align="center">          
          <tr > 
            <td bgcolor="#0000CC" align="center" ><font color="#FFFFFF">���O</font>  
                <input type="text" name="satyno">
				<input type="text" name="satyname">
                <input type="submit" name="Submit" value="�R��">
            </td>			
          </tr> 
	 </table>        
</table>
</form>

