<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body onLoad="window.print()">
<?php
// -------------���X�Ҧ��i�f�檺���---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT transaction.* FROM transaction WHERE (trandate >='$trandate1' and trandate<='$trandate2' and tranvendno='$tranvendno') ";	
	$res = mysql_query($SQLStr);
	
//--------------�p���`���Ƥέ���------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>
<!---�C�L�����^���� ------>
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="596" border="0" align="center" cellspacing="0" cellpadding="0" >
    <tr > 
      <td width="619"  align="left">
<?php
//--------------���ƿ�ܧe�{�γs��---------------
     echo "�t�����I�b�ڪ�&nbsp;&nbsp; ��&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
	    echo "�t�ӽs��:".$outicustno." ";
		echo "  <a href=index.php?Select=248&page=$i>$i</a>|";
	}
       echo "��, �@".$total."��&nbsp;&nbsp";
?> 
    </td>
    </tr>
  </table>
  <table width="595" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td width="691"> 
        <table width="593" border="0" align="center" >
		  <tr> 
            <td  align="left" colspan="7"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>    
          <tr> 
		     <td width="63" align="left" ><font size="-1">  
              �i�f���</font>
            </td>                     
            <td width="71" align="left" ><font size="-1">  
             �i�f�渹</font> 
            </td>
            <td width="90" align="left" ><font size="-1"> 
			���~�s��</font> 
            </td>           
            <td width="123" align="left" ><font size="-1"> 
			���~�W��</font>  
            </td>			
			<td width="54" align="left" ><font size="-1"> 
			�ƶq</font> 
            </td> 
			 <td width="75" align="left" ><font size="-1"> 
			 ���</font> 
            </td>  
			 <td width="87" align="left" ><font size="-1">  
              ���B</font></td>    
          </tr>
		  <tr> 
            <td  align="left" colspan="7"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>   		  
	<?php
	
//--------------��ܭ��ƶi�f���Ƨe�{�γs���קﭶ���\��-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
	  $SQLStr="select * from transaction WHERE (trandate >='$trandate1' and trandate<='$trandate2' and tranvendno='$tranvendno' ) limit $first , 10";
	  $res = mysql_query($SQLStr);
	  while (list($trancode, $trandate, $tranno, $tranpono, $tranremark, $tranvendno, $tranprodno, $tranprodname, $tranprodqty, $tranunit, $tranpric, $tranamt)=mysql_fetch_row($res))
		{		
//--------------- ����ƪ�����Ƨe�{---------------
            echo "<tr border='0'   >";	
			echo "<td align='left'><font size='-1'>" . $trandate . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $tranno . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $tranprodno  . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $tranprodname . "</font></td>\n";
			echo "<td align=left''><font size='-1'>" . $tranprodqty . "</font></td>\n";			
			echo "<td align='left'><font size='-1'>" . $tranpric . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $tranamt . "</font></td>\n";
			echo "</tr>";		  	
		}	
?>   
        </table>
      </td>
    </tr>
  </table>    
</form>
</body>
</html>