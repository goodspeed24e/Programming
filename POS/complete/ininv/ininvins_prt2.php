<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body onLoad="window.print()">
<?php
// -------------���X�Ҧ��i�f�檺���---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT transaction.* FROM transaction WHERE (trandate >='$trandate1' and trandate<='$trandate2') ";	
	$res = mysql_query($SQLStr);
	
//--------------�p���`���Ƥέ���------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/30);
?>
<!----����C�L����,�^�D�ؿ�------>
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="596" border="0" align="center" cellspacing="0" cellpadding="0" >
    <tr > 
      <td width="603" align="left">
		 <?php
//--------------���ƿ�ܧe�{�γs��---------------
     echo "�i�f�����&nbsp;&nbsp;<br><font size='-1'>�i�f���".$trandate1."��".$trandate2. "��&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=../index.php?Select=370&page=$i>$i</a>|";
	}
       echo "��, �@".$total."��&nbsp;&nbsp</font>";
?> 
    </td>
    </tr>
  </table>
  <table width="598" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td width="782"> 
        <table width="596" border="0" align="center" >
		   <tr> 
            <td  align="left" colspan="6"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>
          <tr>
		   <td width="112"  align="left"><font size="-1"> 
             �i�f���</font>
            </td>  
			<td width="112"  align="left"><font size="-1"> 
             �i�f�渹</font>
            </td>                      
            <td width="112" align="left"><font size="-1"> 
             ���~�s��</font>
            </td>
            <td width="112"  align="left"><font size="-1"> 
             ���~�W��</font>
            </td>          
            <td width="61" align="left"><font size="-1"> 
              �t��</font>
            </td>
			 <td width="61"  align="left"><font size="-1"> 
              �ƶq</font>
            </td> 				                 
          </tr>	
		   <tr> 
            <td  align="left" colspan="6"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>	  
	<?php
//--------------��ܭ��ƶi�f���Ƨe�{�γs�������\��-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=30*($page - 1);
	  $SQLStr="select * from transaction WHERE (trandate >='$trandate1' and trandate<='$trandate2') limit $first , 30";
	  $res = mysql_query($SQLStr);	 
       while (list($trancode, $trandate, $tranno, $tranpono, $tranremark, $tranvendno, $tranprodno, $tranprodname, $tranprodqty, $tranunit, $tranpric, $tranamt)=mysql_fetch_row($res))
		 {
//------------------------- �����ƪ���ƨçe�{------------------
            echo "<tr border='0'>";	
			echo "<td align='left'><font size='-1'>" . $trandate  . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $tranno  . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $tranprodno  . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $tranprodname . "</font></td>\n";			
			echo "<td align='left'><font size='-1'>" . $tranvendno . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $tranprodqty . "</font></td>\n";				
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
