<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body onLoad="window.print()">
<?php
		include("mysqlcntdb.php"); 
		$SQLStr3 = "SELECT * FROM vend WHERE (vendno >='$vendno1' and vendno <='$vendno2')";		
		$res = mysql_query($SQLStr3);
		$j=mysql_num_rows($res);

?>
<form name="form1" method="post" action="../index.php">
  <table width="924" border="0" align="center">
    <tr>
      <td width="914">
        <table width="100%" border="0">
          <tr>
            <td>
              <div  align="left">�t�Ӥ@����</div>
            </td>
          </tr>
		  <tr>	
		  <td align='left'  height='21'><font size='-1'>�s��: <?php echo $vendno1 ?> �� <?php echo $vendno2 ?></font></td>
		  </tr>	
        </table>
        <table width="100%" border="0">
          <tr> 
            <td colspan="7"> 
              <hr size="1" color="#000000" width="100%">
            </td>
          </tr>
          <tr>           
			<td height="23" width="70"><font size="-1">
              <div  align="left">�t�ӽs��</div></font> 
            </td>
            <td height="23" width="77"><font size="-1"> 
              <div align="left">�t��²��</div></font>
            </td>
			 <td height="23" width="67"><font size="-1"> 
              <div align="left">�Τ@�s��</div></font>
            </td>			
            <td height="23" width="58"><font size="-1"> 
              <div align="left">�p���H</div></font>
            </td>
            <td width="73" height="23"><font size="-1"> 
              <div align="left">�p���q��</div></font>
            </td>
            <td height="23" width="80"><font size="-1"> 
              <div align="left">�p�����</div></font>
            </td>
            <td width="421" height="23" colspan="3"><font size="-1"> 
              <div align="left">�t�Ӧa�}</div></font>
            </td>           
          </tr>
		   <tr> 
            <td colspan="7"> 
              <hr size="1" color="#000000" width="100%">
            </td>
          </tr>
		 
<? 
	// �Y�t�Ӹ�ƪ����Ȥ���
	if (mysql_num_rows($res)>0)
	{
	  $num = mysql_num_rows($res);	 
	  // �e�{�t�Ӹ�ƪ��e
	  for ($i=0;$i<$num;$i++)
	  {
		$row = mysql_fetch_array($res);		
		if(!$row) 
			break; 		
		echo "<tr>";	
		echo "<td width='50' height='21' align='left'><font size='-1'>" . $row['vendno'] . "</font></td>";
		echo "<td width='60' height='21' align='left'><font size='-1'>" . $row['vendsname'] . "</font></td>";
		echo "<td width='80' height='21' align='left'><font size='-1'>". $row['vendinvoice'] . "</font></td>";
		echo "<td width='80' height='21' align='left'><font size='-1'>". $row['vendcontact'] . "</font></td>";
		echo "<td width='80' height='21' align='left'><font size='-1'>". $row['vendtel'] . "</font></td>";
		echo "<td align='left' width='80' height='21'><font size='-1'>" . $row['vendmobil'] . "</font></td>";
		echo "<td width='200' height='21' align='left'><font size='-1'>" . $row['vendadr'] . "</font></td></tr>";			
		echo " <tr> 
            <td colspan='7'>
		         <hr size='1' color='#999999' width='100%'>
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
                <input type="button" name="CONT" value="����" onClick="window.close();">
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
