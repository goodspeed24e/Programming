<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php 
    // -------------���X�Ҧ����ʥD��ƪ�O�����i�f�����---------------
	include("mysqlcntdb.php");
	$dt=date("Y-m-d");	
	$SQLStr = "SELECT * FROM  purchmst WHERE purcmdate >= '$dt'";
	$res = mysql_query($SQLStr);
    //--------------�p���`���Ƥέ���------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>
<!------�ǵ�purchasehaste_prt2.php,����j�M---->
<form name="form1" method="post" action="purchase/purchasehaste_prt2.php?purcmtranno=' . $purcmtranno . '">
  <table width="782" border="1" align="center" cellspacing="0" cellpadding="0" >
    <tr bgcolor="#99CCFF"> 
      <td align="center">
<?php
    //--------------���ƿ�ܧe�{�γs��---------------
     echo "�ʳf���&nbsp;&nbsp; ��&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=280&page=$i>$i</a>|";
	}
       echo "��, �@".$total."��&nbsp;&nbsp";
?> 
    </td>
    </tr>
  </table>
  <table width="782" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td> 
        <table width="782" border="1" align="center" bgcolor="#FFFFFF">
          <tr>                     
            <td bgcolor="#99CCFF" align="center"> 
             ���ʳ渹
            </td>
            <td bgcolor="#99CCFF" align="center"> 
             �����t��
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              ��f���
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              �������O
            </td>             
          </tr>		  
	<?php
      //--------------��ܭ���,���ʥD��ƪ�O�����i�f��Ƨe�{�γs�������\��-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
	  $SQLStr="select * from purchmst   WHERE purcmdate >= '$dt'  limit $first , 10";
	  $res = mysql_query($SQLStr);	  	
       while (list($purcmtranno, $purcmvend,  $purcmdate, $purcmtype)=mysql_fetch_row($res))
		{
        //--------------- ������ʥD��ƪ�O�����i�f��ƨçe�{-----------------------
            echo "<tr border='0'   bgcolor='#ffffff'>";			
			echo "<td align='center'><a href='purchase/purchasehaste_prt2.php?purchtranno=" . $purcmtranno . "&purcmdate=".$purcmdate."&purcmvend=".$purcmvend."'>" . $purcmtranno . "</a></td>\n";
			echo "<td align='center'>" . $purcmvend  . "</td>\n";
			echo "<td align='center'>";
			   if ($purcmdate == '') 
			      $purcmdate="�L���";	        
			      echo  $purcmdate . "</td>\n";
            echo "<td align='center'>";			  
			   if ($purcmtype == '') 
			      $purcmtype="�ӺD��";	        
			      echo  $purcmtype . "</td>\n";
			echo "</tr>";		  	
		}	
?>         <tr>                     
            <td bgcolor="#99CCFF" align="center" colspan="4"> 
             <font color="#FF0000">�w�q�ʥ��W�L����ݶʳf���~��T���</font>
            </td>                       
        </table>
      </td>
    </tr>
  </table>    
</form>
</body>
</html>
