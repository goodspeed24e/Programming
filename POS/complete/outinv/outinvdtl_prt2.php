<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body onLoad="window.print()">
<?php
// -------------���X�Ҧ��P�f�檺���---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT outinv.* FROM outinv WHERE (outidate >='$outidate1' and outidate<='$outidate2') ";	
	$res = mysql_query($SQLStr);
	
//--------------�p���`���Ƥέ���------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/30);
?>
<!----����C�L����,�^�D�ؿ�------>
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="592" border="0" align="center" cellspacing="0" cellpadding="0" >
    <tr > 
      <td width="687" align="left">
		 <?php
//--------------���ƿ�ܧe�{�γs��---------------
     echo "�P�f�����&nbsp;&nbsp; <br><font size='-1'>�P�f���".$outidate1."��".$outidate2. "��&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=../index.php?Select=410&page=$i>$i</a>|";
	}
       echo "��, �@".$total."��&nbsp;&nbsp</font>";
?>
    </td>
    </tr>
  </table>
  <table width="596" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td width="596"> 
        <table width="596" border="0"  align="left" >
		 <tr> 
            <td  align="left" colspan="7"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>
          <tr> 
		   <td width="70" align="left" ><font size="-1">  
             �P�f���</font>
            </td>  
			<td width="68" align="left" ><font size="-1"> 
             �P�f�渹</font>
            </td>                      
            <td width="84" align="left" ><font size="-1"> 
             ���~�s��</font>
            </td>
            <td width="108" align="left" ><font size="-1"> 
             ���~�W��</font>
            </td>          
            <td width="96" align="left" ><font size="-1"> 
              �Ȥ�</font>
            </td>
			 <td width="60" align="left" ><font size="-1"> 
              �ƶq</font>
            </td>  
			<td width="80" align="left" ><font size="-1"> 
              ���</font>
            </td>      
          </tr>
		   <tr> 
            <td  align="left" colspan="7"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>		  
	<?php
//--------------��ܭ��ƾP�f���Ƨe�{�γs�������\��-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=30*($page - 1);
	  $SQLStr="select * from outinv WHERE (outidate >='$outidate1' and outidate<='$outidate2') limit $first , 30";
	  $res = mysql_query($SQLStr);	  
	  while (list($outicode, $outino, $outiprodno, $outidate, $outiremark, $outicustno, $outiprodname, $outiprodqty, $outiunit, $outipric, $outiamt)=mysql_fetch_row($res))
		{
//------------------------- �����ƪ���ƨçe�{�P�f���------------------
             echo "<tr border='0' >";	
			echo "<td align='left'><font size='-1'>" . $outidate  . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $outino  . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $outiprodno  . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $outiprodname . "</font></td>\n";			
			echo "<td align='left'><font size='-1'>" . $outicustno . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $outiprodqty . "</font></td>\n";	
            echo "<td align='left'><font size='-1'>" . $outiunit . "</font></td>\n";			
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
