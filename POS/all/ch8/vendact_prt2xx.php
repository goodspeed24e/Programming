<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��vendact_prt2</title>
</head>
<body onLoad="window.print()">
<?php
		include("mysqlcntdb.php"); 
//---------------�إ�vend��ƪ�,�d�ߦr��------------------------------		
		$SQLStr3 = "SELECT * FROM vend WHERE (vendno >='$vendno1' and vendno <='$vendno2')";		
		$res = mysql_query($SQLStr3);
		$j=mysql_num_rows($res);			
?>
<!----����C�L����,�^����----------->
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="924" border="0" align="center" cellpadding="0" cellspacing="0">
    <tr >
      <td width="914">
        <table width="67%" border="0">
          <tr>
            <td>
              <div align="left">�t�ӷ|�p��س]�w��</div>
            </td>
          </tr>
        </table>
        <table width="67%" border="0" cellpadding="0" cellspacing="0">
		   <tr> 
            <td  align="left" colspan="9"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>          
          <tr>           
			<td height="23" width="48"><font size="-1"> 
              <div align="left">�t�Ӹ�</div></font>
            </td>
            <td height="23" width="54"><font size="-1"> 
              <div align="left">²��</div></font>
            </td>
			 <td height="23" width="57"><font size="-1"> 
              <div align="left">�Τ@�s��</div></font>
            </td>			
            <td height="23" width="54"><font size="-1"> 
              <div align="left">�p���H</div></font>
            </td>
            <td width="64" height="23"><font size="-1"> 
              <div align="left">�p���q��</div></font>
            </td>
            <td width="62" height="23" ><font size="-1"> 
              <div align="left">�p�����</div></font>
            </td>
            <td width="94" height="23" ><font size="-1">  
              <div align="left">�W�����B�s��</div></font>
            </td>
			 <td width="88" height="23" ><font size="-1"> 
              <div align="left">�������B�s��</div></font>
            </td>   
			 <td width="91"  height="23" ><font size="-1"> 
              <div align="left">�䲼���B�s��</div></font>
            </td>              
          </tr>
		   <tr> 
            <td  align="left" colspan="9"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>      
		 
<? 
//------------------------ �Y�t�Ӹ�ƪ����j�M�X���e-----------------  	
	if (mysql_num_rows($res)>0)
	{
	  $num = mysql_num_rows($res);	
	   
//------------------------- �e�{�t�Ӹ�ƪ�椺�e--------------------- 
	  for ($i=0;$i<$num;$i++)
	  {
		$row = mysql_fetch_array($res);
//-------------------------���浲��,���X�j��------------------------				
		if(!$row) 
			break;	
//--------------------------�e�{�C�L���e--------------------------				
		echo "<tr>";		
		echo "<td width='60' height='21' align='left'><font size='-1'>" . $row['vendno'] . "</font></td>";
		echo "<td width='60' height='21' align='left'><font size='-1'>" . $row['vendsname'] . "</font></td>";
		echo "<td width='100' height='21' align='left'><font size='-1'>". $row['vendinvoice'] . "</font></td>";
		echo "<td width='100' height='21' align='left'><font size='-1'>". $row['vendcontact'] . "</font></td>";
		echo "<td width='100' height='21' align='left'><font size='-1'>". $row['vendtel'] . "</font></td>";
		echo "<td align='left' width='60' height='21'><font size='-1'>" . $row['vendmobil'] . "</font></td>";
		echo "<td  height='21' align='left'><font size='-1'>" . $row['vendprepdc'] . "</font></td>";
		echo "<td align='left'  height='21'><font size='-1'>" . $row['vendapdc'] . "</font></td>";
		echo "<td align='left'  height='21'><font size='-1'>" . $row['vendchkdc'] . "</font></td></tr>";
		echo "  <tr> 
            <td colspan='10'> 
              <hr>
            </td>
          </tr>";
	  }
	}
?>        
        </table>
        <hr>
        <table width="67%" border="0">
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
