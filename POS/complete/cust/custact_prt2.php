<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body onLoad="window.print()">
<?php
		include("mysqlcntdb.php"); 
		$SQLStr3 = "SELECT * FROM cust WHERE (custno >='$custno1' and custno <='$custno2')";		
		$res = mysql_query($SQLStr3);
		$j=mysql_num_rows($res);			
?>
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="924" border="0" align="center" cellpadding="0" cellspacing="0">
    <tr>
      <td width="914">
        <table width="100%" border="0">
          <tr>
            <td>
              <div  align="left">�Ȥ�|�p��س]�w��</div>
            </td>
          </tr>
		  <tr>	
		  <td align='left'  height='21'><font size='-1'>�s��: <?php echo $custno1 ?> �� <?php echo $custno2 ?></font></td>
		  </tr>	
        </table>
        <table width="100%" border="0" cellpadding="0" cellspacing="0">
          <tr> 
            <td  align="left" colspan="9"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>
          <tr>           
			<td height="23" width="63"><font size="-1"> 
              <div  align="left">�Ȥ�s��</div></font>
            </td>
            <td height="23" width="62"><font size="-1"> 
              <div align="left">�Ȥ�²��</div></font>
            </td>
			 <td height="23" width="62"><font size="-1"> 
              <div align="left">�Τ@�s��</div></font>
            </td>			
            <td height="23" width="48"><font size="-1"> 
              <div align="left">�p���H</div></font>
            </td>
            <td width="65" height="23"><font size="-1"> 
              <div align="left">�p���q��</div></font>
            </td>
            <td width="67" height="23" ><font size="-1"> 
              <div align="left">�p�����</div></font>
            </td>
            <td width="79" height="23" > 
              <div align="left"><font size="-1">�w�����</font></div>
            </td>
			 <td width="82" height="23" > 
              <div align="left"><font size="-1">�������</font></div>
            </td>   
			 <td width="386"  height="23" > 
              <div align="left"><font size="-1">�䲼���</font></div>
            </td>              
          </tr>	
		    <tr> 
            <td  align="left" colspan="9"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>		
<?php 
//---------- �Y�Ȥ��ƪ�����Ƥ��e---------- 	
	if (mysql_num_rows($res)>0)
	{
	  $num = mysql_num_rows($res);	 
//---------- �e�{�Ȥ��ƪ��e---------------- 
	  for ($i=0;$i<$num;$i++)
	  {
		$row = mysql_fetch_array($res);	
// �Y���G�C���w�L���,��������			
		if(!$row) 
			break; 
		echo "<tr>";		
		echo "<td width='60' height='21' align='left'><font size='-1'>" . $row['custno'] . "</font></td>";
		echo "<td width='60' height='21' align='left'><font size='-1'>" . $row['custsname'] . "</font></td>";
		echo "<td width='100' height='21' align='left'><font size='-1'>". $row['custinvoice'] . "</font></td>";
		echo "<td width='100' height='21' align='left'><font size='-1'>". $row['custcontact'] . "</font></td>";
		echo "<td width='100' height='21' align='left'><font size='-1'>". $row['custtel'] . "</font></td>";
		echo "<td align='left' width='60' height='21'><font size='-1'>" . $row['custmobil'] . "</font></td>";
		echo "<td  height='21' align='left'><font size='-1'>" . $row['custprepdc'] . "</font></td>";
		echo "<td align='left'  height='21'><font size='-1'>" . $row['custsaledc'] . "</font></td>";
		echo "<td align='left'  height='21'><font size='-1'>" . $row['custchkdc'] . "</font></td></tr>";
		echo "  <tr> 
            <td colspan='9'> 
              <hr>
            </td>
          </tr>";
	  }
	}
?>        
        </table>
        <hr>
        <table width="100%" border="0">
          <tr >            
            <td height="23"> 
              <div  align="center"> 
                <input type="button" name="windowsclose" value="����" onClick="window.close();">
              </div>
            </td>
            <td height="23" > 
              <div align="left">
                &nbsp;
              </div>
            </td>
          </tr>
          <tr>
            <td colspan="4" align='center'>
            </td>
          </tr>
        </table>
      </td>
    </tr>
  </table>
  </form> 
</body>
</html>
